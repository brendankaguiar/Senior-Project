#*************DESCRIPTION*************
#Written by Daniel Beeston
#Currently a test script for client behavior, does not do anything useful

import sqlite3
import socket
import requests
import time
from datetime import datetime
import random


t = int(time.time())
d = str(datetime.today().date())
d = d.replace('-','_')


#HOST = 'http://75.38.110.170:5000/'  # The server's hostname or IP address
#ROUTE = '/devicedata/0/'+d
HOST = 'https://flask-rews.herokuapp.com/'
#HOST = 'http://127.0.0.1:5000/'  # The server's hostname or IP address
ROUTE = '/devicedata/metadata/0'

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