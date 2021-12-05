import sqlite3
import socket
import requests
import time
from datetime import datetime
import random
import math

HOST = 'http://127.0.0.1:5000'  # The server's hostname or IP address
#HOST = 'http://75.38.110.170:5000/'
ROUTE = '/devicedata/all/0/'

wind_direction = ['N','NW','NE','S','SW','SE']

start_datetime = datetime(2021,11,29,0,0,0)
end_datetime = datetime(2021,12,6,12,0,0)

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
    current_timestamp+=60
