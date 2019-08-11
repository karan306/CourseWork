import pyaudio 
import wave
from sys import byteorder
from array import array
from scipy.fftpack import fft
import numpy as np
from datetime import datetime
import constants
CHUNK = 1024
FORMAT = pyaudio.paInt32
CHANNELS = 1
RATE = 48000
BIT_SECONDS = 0.1
def record():
	audio = pyaudio.PyAudio()
	stream = audio.open(format=FORMAT,
                channels=CHANNELS,
                rate=RATE,
                input=True,
                frames_per_buffer=CHUNK)
	frames = []
	frequencies=[]
	while True:
		s = array('h')
		for i in range(0, int(RATE / CHUNK * BIT_SECONDS)):
			data = stream.read(CHUNK)
			frames.append(data)
			snd_data = array('h', data)
			if byteorder == 'big':
				snd_data.byteswap()
			s.extend(snd_data)
		if nearer(getFrequency(s))==3:
			continue
		else :
			break

	stop=0
	print("###RECORDING###")
	while stop <= 3:
		print "kaka"
		s = array('h')
		for i in range(0, int(RATE / CHUNK * BIT_SECONDS)):
			data = stream.read(CHUNK)
			frames.append(data)
			snd_data = array('h', data)
			if byteorder == 'big':
				snd_data.byteswap()
			s.extend(snd_data)
		rev_freq=nearer(getFrequency(s))
		if rev_freq == 3:
			stop+=1
		else:
			frequencies.append(s)
	print("###RECORDING DONE###")

	stream.stop_stream()
	stream.close()
	audio.terminate()
	frequencies=map(lambda x:getFrequency(x),frequencies)
	return frequencies

def getFrequency(x):
	X = fft(x)
	freq = (np.abs(X)).argmax() / BIT_SECONDS + 1
	return freq*2


def nearer(x):
	return np.argmin(map(lambda k: abs(k-x),constants.frequencies))




if __name__ == '__main__':
	from decoder import decoder
	x,y= decoder(record())
	print x
	print y