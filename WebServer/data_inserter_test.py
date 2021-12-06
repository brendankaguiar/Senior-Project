import sqlite3
import socket
import requests
import time
from datetime import datetime
import random
import math

#*************PURPOSE*************
#When ran, will post data in a range of "hours" to now, then start posting once a minute
#For example, if hours is 6, and the current time is 12pm, it will post datapoints from 6am to 12pm, then start posting once a minute


#*****CHANGE IF NEEDED*****
hours = 6

HOST = 'http://127.0.0.1:5000'  # The server's hostname or IP address
#HOST = 'http://75.38.110.170:5000/'
ROUTE = '/devicedata/all/0/'

wind_direction = ['N','NW','NE','S','SW','SE']

start_datetime = datetime.now().timestamp() - (3600*hours)
start_datetime = datetime.fromtimestamp(start_datetime)
end_datetime = datetime.now()

start_timestamp = int(start_datetime.timestamp())
end_timestamp = int(end_datetime.timestamp())

current_hour = 0
current_wind = 'NW'
current_timestamp = start_timestamp
while current_timestamp <= end_timestamp:
    t = datetime.fromtimestamp(current_timestamp)
    d = str(t.date())
    d = d.replace('-','_')

    if t.hour != current_hour:
        current_hour = t.hour
        current_wind = wind_direction[random.randint(0,5)]


    #get random temp:
    temp = 12*math.cos((t.hour+12)/(12/math.pi))+32 + random.uniform(-0.5,0.5)
    temp = ((temp-32)*5)/9  #convert to celcius

    wind_speed = 10 * math.cos((t.hour+6)/(6/math.pi))+10 + random.uniform(0,1)
    aqi = 25+random.randint(-1,1)
    aqi += random.randint(0,1)

    try:
        req = requests.post(HOST+ROUTE+d,json={"timestamp": int(current_timestamp),
                                               "date": d,
                                               "deviceid": 0,
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
        print(f"{HOST}{ROUTE}{d}")
    current_timestamp+=60

def postnow():
    t = datetime.now()
    current_timestamp = int(t.timestamp())
    d = str(t.date())
    d = d.replace('-','_')

    #get random wind direction:
    current_wind = wind_direction[random.randint(0,5)]

    #get random temp:
    temp = 12*math.cos((t.hour+12)/(12/math.pi))+32 + random.uniform(-0.5,0.5)
    temp = ((temp-32)*5)/9  #convert to celcius

    wind_speed = 10 * math.cos((t.hour+6)/(6/math.pi))+10 + random.uniform(0,1)
    aqi = 25+random.randint(-1,1)
    aqi += random.randint(0,1)

    try:
        req = requests.post(HOST+ROUTE+d,json={"timestamp": int(current_timestamp),
                                               "date": d,
                                               "deviceid": 0,
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

while True:
    postnow()
    time.sleep(60)
