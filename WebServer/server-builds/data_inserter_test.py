#*************DESCRIPTION*************
#Written by Daniel Beeston
#Used to generate hours worth of dummy data for the server and then inserts data every minute afterward, mimicing the weather station
#When ran, will post data in a range of "hours" to now, then start posting once a minute
#For example, if hours is 6, and the current time is 12pm, it will post datapoints from 6am to 12pm, then start posting once a minute

#External packages used: requests, time, datetime, random, math

import requests
import time
from datetime import datetime
import random
import math

#*****Number of hours worth of data to generate before current time*****
hours = 6

HOST = 'http://127.0.0.1:5000'  # The server's hostname or IP address
#HOST = 'http://75.38.110.170:5000/'
ROUTE = '/devicedata/all/0/'

wind_direction = ['N','NW','NE','S','SW','SE']

#Get chosen timeframe based on hours variable
start_datetime = datetime.now().timestamp() - (3600*hours)
start_datetime = datetime.fromtimestamp(start_datetime)
end_datetime = datetime.now()   #timeframe ends at current time

start_timestamp = int(start_datetime.timestamp())
end_timestamp = int(end_datetime.timestamp())

current_hour = 0
current_wind = 'NW'
current_timestamp = start_timestamp

#Attempt insert requests to server until current timestamp > end timestamp
while current_timestamp <= end_timestamp:
    t = datetime.fromtimestamp(current_timestamp)
    d = str(t.date())
    d = d.replace('-','_')

    decimalhour = t.hour + (t.minute/60)    #get decimal hour for temp and windspeed functions

    #get fake wind direction, change once per hour
    if t.hour != current_hour:
        current_hour = t.hour
        current_wind = wind_direction[random.randint(0,5)]

    #get fake temp:
    temp = 12*math.cos((decimalhour+12)/(12/math.pi))+32 + random.uniform(-0.5,0.5)
    temp = ((temp-32)*5)/9  #convert to celcius

    #get fake windspeed
    wind_speed = 5 * math.cos((decimalhour+6)/(6/math.pi))+ 5.5 + random.uniform(-0.5,0.5)

    #get random aqi around 25
    aqi = 25+random.randint(-1,1)
    aqi += random.randint(0,1)

    #get random humidity from 45% to 55%
    humidity = random.randint(45,55)

    #get random pressure around Reno's average
    pressure = round(858.78 + round(random.uniform(-0.05,0.05),3),3)

    try:    #attempt to post all data to server as a JSON object
        req = requests.post(HOST+ROUTE+d,json={"timestamp": int(current_timestamp),
                                               "date": d,
                                               "deviceid": 0,
                                               "temperature": round(temp,2),
                                               "windspeed": round(wind_speed,2),
                                               "winddirection": current_wind,
                                               "humidity": humidity,
                                               "pressure": pressure,
                                               "aqi": aqi
                                               })
        print(f"{current_timestamp}, {t}, {req.content.decode()}")
    except: #print error if post failed
        print(f"Error Posting {current_timestamp}")
        print(f"{HOST}{ROUTE}{d}")
    current_timestamp+=60

#Posts a new dummy record to server using current date/time
def postnow():
    t = datetime.now()
    current_timestamp = int(t.timestamp())
    d = str(t.date())
    d = d.replace('-','_')

    decimalhour = t.hour + (t.minute/60)

    #get fake wind direction
    current_wind = wind_direction[random.randint(0,5)]

    #get fake temp:
    temp = 12*math.cos((decimalhour+12)/(12/math.pi))+32 + random.uniform(-0.5,0.5)
    temp = ((temp-32)*5)/9  #convert to celcius

    #get fake windspeed
    wind_speed = 5 * math.cos((decimalhour+6)/(6/math.pi))+ 5.5 + random.uniform(-0.5,0.5)

    #get random aqi around 25
    aqi = 25+random.randint(-1,1)
    aqi += random.randint(0,1)

    #get random humidity from 45% to 55%
    humidity = random.randint(45,55)

    #get random pressure around Reno's average
    pressure = round(858.78 + round(random.uniform(-0.05,0.05),3),3)

    try:
        req = requests.post(HOST+ROUTE+d,json={"timestamp": int(current_timestamp),
                                               "date": d,
                                               "deviceid": 0,
                                               "temperature": round(temp,2),
                                               "windspeed": round(wind_speed,2),
                                               "winddirection": current_wind,
                                               "humidity": humidity,
                                               "pressure": pressure,
                                               "aqi": aqi
                                               })
        print(f"{current_timestamp}, {t}, {req.content.decode()}")
    except:
        print(f"Error Posting {current_timestamp}")
    current_timestamp+=60

#Post a new record every minute until script is exited
while True:
    postnow()
    time.sleep(60)
