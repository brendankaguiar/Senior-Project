#Serial Import 
#Version 0.1 Still need to parse junk before sending values - Brendan A.
#Version 0.2 Decoded Data. Can either parse values or read one at a time
#after start symbol is found - Brendan A. 
import serial
from time import sleep
port = serial.Serial("/dev/ttyS0",9600)#timeout opt. paramater
while True:
	Data = port.read()	#read serial port
	Sleep(.05)#increasing time retains more of value		
	data_left = port.inWaiting()	#check for remaining bytes
	Data += port.read(data_left)
	Start = Data.decode("utf-8")#decode Arduino Weather Data
	#if Start == '$':#if start symbol found
        	#i == 1
        	#while i < 7 #loop for serial read of each data point
			#Begin parsing
	#elif Start == '!' #if error symbol found
		#i == 1
		#while i < size_error_data_points
	print(Start)#used to test that data was successfully read
	