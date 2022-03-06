#Reqests and Time functions written by Daniel B.
#serial and time functions written by Brendan A.

#External packages used: requests, serial, sleep, datetime

import serial
from time import sleep
import requests
from datetime import datetime
import math
import json
import RPi.GPIO as GPIO

device = 0

HOST = 'https://flask-rews.herokuapp.com'
ROUTE = '/devicedata/all/0/'

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(18,GPIO.OUT)
GPIO.setup(23,GPIO.OUT)

for i in range(4):
    sleep(0.5)
    GPIO.output(18,GPIO.HIGH)
    GPIO.output(23,GPIO.HIGH)
    sleep(0.5)
    GPIO.output(18,GPIO.LOW)
    GPIO.output(23,GPIO.LOW)
    
#sleep(15)

port = serial.Serial("/dev/ttyACM0",9600, bytesize=serial.EIGHTBITS, parity=serial.PARITY_NONE, stopbits=serial.STOPBITS_TWO, timeout=30, write_timeout=30)#wait until data available
cycles = 0


while True:
    date = str(datetime.today().date())
    date = date.replace('-','_')
    now = datetime.now()
    current_timestamp = now.timestamp()
    
    GPIO.output(23,GPIO.LOW)
    GPIO.output(18,GPIO.LOW)
    
    try:
        Data = port.read()  #read serial port
        sleep(.05)#increasing time retains more of value        
        data_left = port.inWaiting()    #check for remaining bytes
        Data += port.read(data_left)
        Start = Data.decode("utf-8")
    except:
        print("read failed")
        GPIO.output(18,GPIO.HIGH)
        sleep(0.5)
        continue
    
    slist = Start.split()
    
    if len(slist) == 6:
        slist[0] = float(slist[0])
        slist[1] = float(slist[1])
        slist[2] = float(slist[2])
        slist[3] = float(slist[3])
        slist[5] = float(slist[5])
    
    for x in slist:
        print(x)
    print("")
    
    #Data = port.readline().decode("utf-8").strip()#decode data received to String
    #print("he")
    #W_Data = Data.split(",")#parse into list removing commas in the process
    #print(W_Data) #check data was parsed correctly
    #append W_Data to json
    
    if cycles > 4:
        try:
            req = requests.post(HOST+ROUTE+date,json={"timestamp": int(current_timestamp),
                                                      "date": date,
                                                      "deviceid": device,
                                                      "temperature": slist[0],
                                                      "windspeed": slist[5],
                                                      "winddirection": slist[4],
                                                      "humidity": slist[1],
                                                      "pressure": slist[2],
                                                      "aqi": slist[3]
                                                      })
            print(req.content.decode())
            if req.content.decode() == "post_success":
                GPIO.output(23,GPIO.HIGH)
            else:
                GPIO.output(18,GPIO.HIGH)
                
        except:
            print(f"Error Posting {current_timestamp}")
            GPIO.output(18,GPIO.HIGH)
    
    sleep(0.5)
    cycles+=1

