#*************DESCRIPTION*************
#Written by Daniel Beeston
#Test script for server. When ran, it will post a single datapoint to localhost server with current date and time
#Script is now somewhat redundent after creating data_inserter_test.py
#To change host, see HOST variable

#External packages used: requests, time, datetime, random, math

import requests
import time
from datetime import datetime
import random
import math

device = 0

#HOST = 'http://75.38.110.170:5000/'  #Brendon's host
HOST = 'http://127.0.0.1:5000/'    #Local host
ROUTE = '/devicedata/all/0/'

wind_direction = ['N','NW','NE','S','SW','SE']

def postnow():
    t = datetime.now()
    current_timestamp = t.timestamp()
    d = str(t.date())
    d = d.replace('-','_')

    decimalhour = t.hour + (t.minute/60)

    #get random wind direction:
    current_wind = wind_direction[random.randint(0,5)]

    #get random temp:
    temp = 12*math.cos((t.hour+12)/(12/math.pi))+32 + random.uniform(-0.5,0.5)
    temp = ((temp-32)*5)/9  #convert to celcius

    wind_speed = 5 * math.cos((decimalhour+6)/(6/math.pi))+ 5.5 + random.uniform(-0.5,0.5)
    aqi = 25+random.randint(-1,1)
    aqi += random.randint(0,1)

    try:
        req = requests.post(HOST+ROUTE+d,json={"timestamp": int(current_timestamp),
                                               "date": d,
                                               "deviceid": device,
                                               "temperature": round(temp,2),
                                               "windspeed": round(wind_speed,2),
                                               "winddirection": current_wind,
                                               "humidity": int(round(random.uniform(0.45,0.55),2)*100),
                                               "pressure": round(858.78 + round(random.uniform(-0.05,0.05),3),3),
                                               "aqi": aqi
                                               })
        print(f"{current_timestamp}, {t}, {req.content.decode()}")
    except:
        print(f"Error Posting {current_timestamp}")
    current_timestamp+=60


postnow()

