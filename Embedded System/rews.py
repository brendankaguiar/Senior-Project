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
ROUTE1 = '/devicedata/all/0/'
ROUTE2 = '/devicedata/metadata/0'

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(18,GPIO.OUT)
GPIO.setup(23,GPIO.OUT)

#Flash red and green LEDs at startup
for i in range(4):
    sleep(0.5)
    GPIO.output(18,GPIO.HIGH)
    GPIO.output(23,GPIO.HIGH)
    sleep(0.5)
    GPIO.output(18,GPIO.LOW)
    GPIO.output(23,GPIO.LOW)
    
#set up serial port
port = serial.Serial("/dev/ttyACM0",9600, bytesize=serial.EIGHTBITS, parity=serial.PARITY_NONE, stopbits=serial.STOPBITS_TWO, timeout=30, write_timeout=30)
cycles = 0


while True:
    #generate current timestamp
    date = str(datetime.today().date())
    date = date.replace('-','_')
    now = datetime.now()
    current_timestamp = now.timestamp()

    #turn of LEDs
    GPIO.output(23,GPIO.LOW)
    GPIO.output(18,GPIO.LOW)

    #wait until data is available
    try:
        Data = port.read()  #read serial port
        sleep(.12)#increasing time retains more of value        
        data_left = port.inWaiting()    #check for remaining bytes
        Data += port.read(data_left)
        Start = Data.decode("utf-8")
    except: #flash red LED if read failed, continue to next loop iteration
        print("read failed")
        GPIO.output(18,GPIO.HIGH)
        sleep(0.5)
        continue

    #split data from arduino into list
    slist = Start.split()

    #check if data is valid (7 fields)
    if len(slist) == 7:
        slist[0] = float(slist[0])
        slist[1] = float(slist[1])
        slist[2] = float(slist[2])
        slist[3] = float(slist[3])
        slist[5] = float(slist[5])
    else:
        #print(f"Error Posting {current_timestamp}")
        #GPIO.output(18,GPIO.HIGH)
        #sleep(0.5)
        continue

    #determine whether GPS data is valid
    valid = False
    if slist[6].find('V') == -1:
        valid = True
        gpslist = slist[6].split(',')
        slist[6] = gpslist[1]+","+gpslist[2]+","+gpslist[3]+","+gpslist[4]
    print(f"Valid: {valid}")
    
    for x in slist:
        print(x)
    print("")

    #skip first three cycles to sync up to arduino
    if cycles > 2:
        #try to post weather data
        try:
            print(HOST+ROUTE1+date)
            req = requests.post(HOST+ROUTE1+date,json={"timestamp": int(current_timestamp),
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
        
        #Try to post location
        try:
            print(slist[6])
            if valid:
                locationreq = requests.post(HOST+ROUTE2,json={"location": slist[6], "lastupdated": int(current_timestamp)})
                
                print(locationreq.content.decode())
        except:
            print("Could not post location")
            
    
    sleep(0.5)
    cycles+=1

