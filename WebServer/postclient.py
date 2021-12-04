#!/usr/bin/env python3

import sqlite3
import socket
import requests
import time
from datetime import datetime
import random
import re
import json

device = 0
date = str(datetime.today().date())
date = date.replace('-','_')

t = int(time.time())
d = str(datetime.today().date())
d = d.replace('-','_')

HOST = 'http://127.0.0.1:5000'  # The server's hostname or IP address
ROUTE = '/devicedata/0/'+d


def post_data(deviceid):
    url = HOST + "/devicedata/all/" + str(deviceid) + "/" + date
    try:
        req = requests.post(url,json={"timestamp": int(time.time())+x,
                                      "date": randomdate,
                                      "deviceid": 0,
                                      "temperature": random.randint(0,100),
                                      "windspeed": random.randint(0,100),
                                      "winddirection": "SW",
                                      "humidity": random.randint(0,100),
                                      "pressure": random.randint(0,100),
                                      "aqi": random.randint(0,100)
                                      })
    except:
        print("Connection Error")


def get_date(deviceid, date : str):
    url = HOST + "/devicedata/all/" + str(deviceid) + "/" + date
    #url = HOST + "/devicedata/latest/" + str(deviceid)
    try:
        req = requests.get(url)
    except:
        return None
    result = req.content.decode()
    return result
    #print(result)



user_input = ''
while user_input != '.exit':
    user_input = input()
    t1 = time.time()
    data = get_date(0,"2021_11_"+user_input)
    responsetime = time.time() - t1
    if data == None:
        print("Connection Error")
        continue
    data = json.loads(data)
    for record in data:
        print(record)
    print("Records: "+ str(len(data)))
    print(f"Response in {str(responsetime)} seconds")
