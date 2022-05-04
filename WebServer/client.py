#*************DESCRIPTION*************
#Written by Daniel Beeston
#Currently a test script for client behavior, does not do anything useful

import sqlite3
import socket
import requests
import time
from datetime import datetime
import random
import math


t = int(time.time())
d = str(datetime.today().date())
d = d.replace('-','_')


#HOST = 'http://75.38.110.170:5000/'  # The server's hostname or IP address
#ROUTE = '/devicedata/0/'+d
HOST = 'https://flask-rews.herokuapp.com/'
#HOST = 'http://127.0.0.1:5000/'  # The server's hostname or IP address
ROUTE = '/devicedata/metadata/0'
#ROUTE = '/devicedata/all/0/'

PORT = 5000        # The port used by the server
#"GET /get/thingy HTTP/1.1\r\nHost:%s\r\n\r\n" % HOST


def get_data(request):
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((HOST, PORT))
        #request = "GET /get/{0} HTTP/1.1\r\nHost:{1}\r\n\r\n".format(request,HOST)
        #print(request)
        s.send(request.encode())
        req = s.recv(1024)
        info = s.recv(1024)
        body = s.recv(1024)
        return [req.decode(),info.decode(),body]

def get_date(deviceid, date : str):
    url = HOST + "/devicedata/" + str(deviceid) + "/" + date
    req = requests.get(url)
    result = req.content.decode()
    return result
    #print(result)


#print('Received', repr(req))
#print('Received', repr(info))
#print('Received', repr(body))

#data = body.decode()
#print(data)

#
#user_input = ''
#while user_input != '.exit':
#    user_input = input()
#    t1 = time.time()
#    data = get_date(0,"2021_11_"+user_input)
#    responsetime = time.time() - t1
#    print(data)
#    print("Records: "+ str(data.count("\n")))
#    print("Response in "+str(responsetime)+" seconds")


def postweather():
    for x in range(0,1):
        #time.sleep(1)
        day = random.randint(1,30)
        hour = random.randint(1,24)
        #minute
        randomdate = datetime(2021,11,randomdate)

        req = requests.post(HOST+ROUTE,json={"timestamp": int(time.time())+x,
                                             "date": randomdate,
                                             "deviceid": 0,
                                             "temperature": random.randint(0,100),
                                             "windspeed": random.randint(0,100),
                                             "winddirection": "SW",
                                             "humidity": random.randint(0,100),
                                             "pressure": random.randint(0,100),
                                             "aqi": random.randint(0,100)
                                             })
        print(req.content.decode())

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


def postdevice():
    for x in range(0,1):
        #time.sleep(1)
        day = random.randint(1,30)
        hour = random.randint(1,24)
        #minute
        randomdate = datetime(2022,4,10,hour)

        req = requests.post(HOST+ROUTE,json={"location": "test0",
                                             "lastupdated": int(randomdate.timestamp())})
        print(req.content.decode())

postdevice()
