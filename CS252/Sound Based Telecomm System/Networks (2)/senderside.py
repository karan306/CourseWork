import time
from generator import generate
from listener import record
from decoder import decoder
from parity_adder import parity_adder
Data1=list(str(raw_input("Please enter the Data_1 :\n")))
print Data1
Data1=map(lambda x:int(x),Data1)
errors1=[]
try:
	errors1=raw_input("Please enter the error_1 bits ',' seperated\n").split(',')
	errors1=map(lambda x: int(x),errors1)
except Exception as e:
	errors1=[]


Data2=list(str(raw_input("Please enter the Data_2 :\n")))
print Data2
Data2=map(lambda x:int(x),Data2)
errors2=[]
try:
	errors2=raw_input("Please enter the error_2 bits ',' seperated\n").split(',')
	errors2=map(lambda x: int(x),errors2)
except Exception as e:
	errors=[]



parity_bits = parity_adder(Data1)
print parity_bits
ErrorData1=Data1
for i in errors1:
	ErrorData1[i]=int(not ErrorData1[i])
ErrorData1.extend(parity_bits)
generate(ErrorData1)
time.sleep(0.5)
Ack=decoder(record())
if Ack==0:
	Data1.extend(parity_bits)
	generate(Data1)
###########################
time.sleep(0.5)
############################
parity_bits = parity_adder(Data2)
ErrorData2=Data2
for i in errors2:
	ErrorData2[i]=int(not ErrorData2[i])
ErrorData2.extend(parity_bits)
generate(ErrorData2)
time.sleep(0.5)
Ack=decoder(record())
if Ack==0:
	Data1.extend(parity_bits)
	generate(Data2)


