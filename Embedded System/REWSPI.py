#Serial Import 
#Version 0.1 Still need to parse junk before sending values - Brendan A.
import serial
from struct import *
from time import sleep
port = serial.Serial("/dev/ttyS0",9600)#timeout opt. paramater
while True:
	Data = port.read()	#read serial port
	Sleep(.03)		
	data_left = port.inWaiting()	#check for remaining bytes
	Data += port.read(data_left)
	W_Data = str(Data)
	print(W_Data)
	