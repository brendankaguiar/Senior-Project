#!/usr/bin/env python3

import sqlite3
import socket
import requests
import time
from datetime import datetime
import random
import re

device = 0
date = str(datetime.today().date())
date = date.replace('-','_')

t = int(time.time())
d = str(datetime.today().date())
d = d.replace('-','_')

HOST = 'http://127.0.0.1:80'  # The server's hostname or IP address
ROUTE = '/devicedata/0/'+d


def post_data(deviceid):
    url = HOST + "/devicedata/all/" + str(deviceid) + "/" + date
    req = requests.post(url,json={"timestamp": int(time.time())+x,
                                         "date": randomdate,
                                         "deviceid": 0,
                                         "temperature": random.randint(0,100),
                                         "windspeed": random.randint(0,100),
                                         "winddirection": "SW",
                                         "humidity": random.randint(0,100),
                                         "pressure": random.randint(0,100),
                                         "aql": random.randint(0,100)
                                         })

def get_date(deviceid, date : str):
    url = HOST + "/devicedata/all/" + str(deviceid) + "/" + date
    req = requests.get(url)
    result = req.content.decode()
    return result
    #print(result)



user_input = ''
while user_input != '.exit':
    user_input = input()
    t1 = time.time()
    data = get_date(0,"2021_11_"+user_input)
    responsetime = time.time() - t1
    print(data)
    print("Records: "+ str(data.count("\n")))
    print(f"Response in {str(responsetime)} seconds")
