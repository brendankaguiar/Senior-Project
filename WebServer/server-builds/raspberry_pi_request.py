#Reqests and Time functions written by Daniel B.
#serial and time functions written by Brendan A.

#External packages used: requests, serial, sleep, datetime

import serial
from time import sleep
import requests
from datetime import datetime

HOST = 'http://75.38.110.170:5000/'
ROUTE = '/devicedata/all/0/'
date = str(datetime.today().date())
date = date.replace('-','_')
now = datetime.now()
current_timestamp = now.strftime("%H:%M:%S")
port = serial.Serial("/dev/ttyS0",9600)#wait until data available
Data = port.readline().decode("utf-8").strip()#decode data received to String
W_Data = Data.split(",")#parse into list removing commas in the process
#print(W_Data) #check data was parsed correctly
#append W_Data to json
try:
    req = requests.post(HOST+ROUTE+date,json={"timestamp": current_timestamp,
                                              "date": date,
                                              "deviceid": 0,
                                              "temperature": W_Data[0],
                                              "windspeed": W_Data[1],
                                              "winddirection": W_Data[2],
                                              "humidity": W_Data[3],
                                              "pressure": W_Data[4],
                                              "aqi": W_Data[5]
                                              })
    print(req.content)
except:
    print(f"Error Posting {current_timestamp}") #replace with your timestamp variable
