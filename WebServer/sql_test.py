#Test to connect and retrieve data from remote database

import psycopg2
import urllib.parse as urlparse
import os
import time

url = urlparse.urlparse("postgres://ntmlgtzglebvxt:7f29de081a06069389993e83b304eabc7a607ec4645a1fca7df79d5f167cf1e5@ec2-54-224-64-114.compute-1.amazonaws.com:5432/d2814k1j2ol13i")
dbname = url.path[1:]
user = url.username
password = url.password
host = url.hostname
port = url.port

print(dbname)

db_con = psycopg2.connect(
    dbname=dbname,
    user=user,
    password=password,
    host=host,
    port=port
)

with db_con:    #open db_con and retrieve latest record
    cursor = db_con.cursor()
    request_str = """SELECT * FROM weather"""
    cursor.execute(request_str)
    result = cursor.fetchall()
    for x in result:
        print(x)


print(time.tzname)
