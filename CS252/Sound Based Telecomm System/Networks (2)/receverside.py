import time
from generator import generate
from listener import record
from decoder import decoder
from error_detection import detection
recevied_data=decoder(record())
err_list=detection(recevied_data)
error=err_list[0]
corrcted_code = err_list[1:]
if error==0:
	print "Data1 recieved is", recevied_data
	generate([1,1])
elif error ==1:
	print "One bit error detection"
	print "Data1 recieved is", corrcted_code
	generate([1,1])
else:
	print "Two bit error detection"
	generate([0,0])
	recevied_data=decoder(record())
	print "Data1 recieved is", recevied_data

# time.sleep(0.1)


recevied_data=decoder(record())
err_list=error_detection(recevied_data)
error=err_list[0]
corrcted_code = err_list[1:]
if error==0:
	print "Data2 recieved is", recevied_data
	generate([1,1])
elif error ==1:
	print "One bit error detection"
	print "Data2 recieved is", corrector(recevied_data)
	generate([1,1])
else:
	print "Two bit error detection"
	generate([0,0])
	recevied_data=decoder(record())
	print "Data2 recieved is", recevied_data