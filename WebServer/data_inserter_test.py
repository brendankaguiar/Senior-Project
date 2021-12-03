import sqlite3
import socket
import requests
import time
from datetime import datetime
import random
import math

HOST = 'http://127.0.0.1:5000'  # The server's hostname or IP address
ROUTE = '/devicedata/0/'

wind_direction = ['N','NW','NE','S','SW','SE']

start_datetime = datetime(2021,11,29,0,0,0)
end_datetime = datetime(2021,12,6,12,0,0)

start_timestamp = start_datetime.timestamp()
end_timestamp = end_datetime.timestamp()

current_hour = 0
current_wind = 'NW'
current_timestamp = start_timestamp
while current_timestamp != end_timestamp:
    t = datetime.fromtimestamp(current_timestamp)
    d = str(t.date())
    d = d.replace('-','_')

    if t.hour != current_hour:
        current_hour = t.hour
        current_wind = wind_direction[random.randint(0,5)]


    #get random temp:
    temp = 12*math.cos((t.hour+12)/(12/math.pi))+32 + random.uniform(-0.5,0.5)
    wind_speed = 10 * math.cos((t.hour+6)/(6/math.pi))+10 + random.uniform(0,1)
    aqi = 25+random.randint(-1,1)
    aqi += random.randint(0,1)

    print(t.hour)
    current_timestamp+=60
    try:
        req = requests.post(HOST+ROUTE+d,json={"timestamp": current_timestamp,
                                               "date": d,
                                               "deviceid": 0,
                                               "temperature": temp,
                                               "windspeed": random.randint(0,100),
                                               "winddirection": current_wind,
                                               "humidity": round(random.uniform(0,1),2),
                                               "pressure": random.randint(0,100),
                                               "aqi": aqi
                                               })
    except:
        print(f"Error Posting {current_timestamp}")

