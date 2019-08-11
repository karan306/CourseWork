import math   
import pyaudio 
import constants
from datetime import datetime

def generate(List):
	p = pyaudio.PyAudio()
	RATE = 4800
	WAVEDATA=''
	BIT_SECONDS=0.3
	BITRATE = 16000
	NUMBEROFFRAMES=int(BITRATE*BIT_SECONDS)
	prev=-1
	for x in List:
		if prev == x:
			# print 2
			FREQUENCY=constants.frequencies[2]		
			for y in xrange(NUMBEROFFRAMES):
 				WAVEDATA = WAVEDATA+chr(int(math.sin(y/((BITRATE/FREQUENCY)/math.pi))*127+128)) 
 		FREQUENCY=constants.frequencies[x]
 		# print x	
 		prev = x	
		for y in xrange(NUMBEROFFRAMES):
 			WAVEDATA = WAVEDATA+chr(int(math.sin(y/((BITRATE/FREQUENCY)/math.pi))*127+128)) 	
		
 	stream=p.open(
 				format = p.get_format_from_width(1), 
                channels = 1, 
                rate = BITRATE, 
                output = True
 			) 
 	stream.write(WAVEDATA)
	stream.stop_stream()
	stream.close()
	p.terminate()
	

if __name__=='__main__':
	generate([1,1,1,0,1,1,1,0,1,1,1,0,0])