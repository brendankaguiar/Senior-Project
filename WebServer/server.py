#*************DESCRIPTION*************
#Written by Daniel Beeston
#Flask server routes and database functions
#Run using "python server.py" to host development server on 127.0.0.1

#External packages used: Flask, sqlite3, os, json, datetime

from flask import Flask, request
import sqlite3 as sl
import psycopg2
from datetime import datetime
import urllib.parse as urlparse
import os
import json

import urllib.parse as urlparse

#DATABASE URL:
DATABASE_URL = "postgres://ntmlgtzglebvxt:7f29de081a06069389993e83b304eabc7a607ec4645a1fca7df79d5f167cf1e5@ec2-54-224-64-114.compute-1.amazonaws.com:5432/d2814k1j2ol13i"

#Contains methods for querying database
class database:


    def __init__(self,
                 url_ : str,
                 reset_ : bool = False):
        self.reset = reset_
        #self.db_filename = name +'.db'

        self.url = urlparse.urlparse(url_)
        self.dbname = self.url.path[1:]
        self.user = self.url.username
        self.password = self.url.password
        self.host = self.url.hostname
        self.port = self.url.port


        db_con = psycopg2.connect(
            dbname=self.dbname,
            user=self.user,
            password=self.password,
            host=self.host,
            port=self.port
        )

        #if reset:   #delete existing database if database reset is true
        #    if os.path.exists(self.db_filename):
        #        os.remove(self.db_filename)

        #db_con = sl.connect(self.db_filename)

        with db_con:    #create weather table
            db_cursor = db_con.cursor()
            db_cursor.execute("""
            CREATE TABLE IF NOT EXISTS weather (
                timestamp INT PRIMARY KEY,
                date TEXT,
                deviceid INT,
                temperature REAL,
                windspeed REAL,
                winddirection TEXT,
                humidity REAL,
                pressure REAL,
                aqi REAL
            );
            """)

        db_con.close()

    #debug function to print all data from a day
    def debug_print(self,month,day):
        db_con = psycopg2.connect(
            dbname=self.dbname,
            user=self.user,
            password=self.password,
            host=self.host,
            port=self.port
        )
        with db_con:
            cursor = db_con.cursor()
            cursor.execute(f"SELECT * FROM weather WHERE date = \"2021_{month}_{day}\";")
            result = cursor.fetchall()
            for row in result:
                print(row)
        db_con.close()

    #public insert query
    def insert(self,table,json_data):
        if table == "weather":
            self._weatherinsert(json_data)

    #private insert for weather data
    def _weatherinsert(self,json_data):
        db_con = psycopg2.connect(
            dbname=self.dbname,
            user=self.user,
            password=self.password,
            host=self.host,
            port=self.port
        )
        with db_con:
            db_cursor = db_con.cursor()
            request_str = """INSERT INTO {0} (timestamp, date, deviceid, temperature, windspeed, winddirection, humidity, pressure, aqi)
                VALUES( {1}, {2}, {3}, {4}, {5}, {6}, {7}, {8}, {9} );
                """.format("weather",
                           int(json_data["timestamp"]),
                           '\''+json_data["date"]+'\'',
                           json_data["deviceid"],
                           json_data["temperature"],
                           json_data["windspeed"],
                           '\''+json_data["winddirection"]+'\'',
                           json_data["humidity"],
                           json_data["pressure"],
                           json_data["aqi"])
            db_cursor.execute(request_str)
            db_cursor.close()

    #Public delete records for either certain
    def delete(self,table,data):
        if table == "weather":
            if data is not None:
                self._weatherdelete(data)
            else:
                self._weatherdeleteall()

    def _weatherdelete(self,date):
        db_con = psycopg2.connect(
            dbname=self.dbname,
            user=self.user,
            password=self.password,
            host=self.host,
            port=self.port
        )
        with db_con:
            db_cursor = db_con.cursor()
            request_str = f"""
            DELETE FROM weather
            WHERE date = \'{date}\'"""
            db_cursor.execute(request_str)
            db_cursor.close()

    def _weatherdeleteall(self):
        db_con = psycopg2.connect(
            dbname=self.dbname,
            user=self.user,
            password=self.password,
            host=self.host,
            port=self.port
        )
        with db_con:
            db_cursor = db_con.cursor()
            request_str = "DELETE FROM weather;"
            db_cursor.execute(request_str)
            db_cursor.close()

    #return all records of a certain date and device
    def getday(self,deviceid,date : str):
        db_con = psycopg2.connect(
            dbname=self.dbname,
            user=self.user,
            password=self.password,
            host=self.host,
            port=self.port
        )
        result = 0
        with db_con:    #open db_con and retrieve records
            cursor = db_con.cursor()
            request_str = f"""SELECT * FROM weather 
            WHERE date = (%s) AND deviceid = {deviceid}
            ORDER BY timestamp ASC;"""
            cursor.execute(request_str,[date])
            result = cursor.fetchall()
        record_list = []
        for record in result:   #convert records into dictionary
            record_dict = {'timestamp':record[0],
                           'date':record[1],
                           'deviceid':record[2],
                           'temperature':record[3],
                           'windspeed':record[4],
                           'winddirection':record[5],
                           'humidity':record[6],
                           'pressure':record[7],
                           'aqi':record[8],
                           }
            #print(record_dict)
            record_list.append(record_dict)
        #return flask.jsonify(json)
        return json.dumps(record_list)  #Return json object array with records

    #return most recent record from a certain device
    def getlatest(self, deviceid):
        db_con = psycopg2.connect(
            dbname=self.dbname,
            user=self.user,
            password=self.password,
            host=self.host,
            port=self.port
        )
        with db_con:    #open db_con and retrieve latest record
            cursor = db_con.cursor()
            request_str = """SELECT * FROM weather
            WHERE timestamp = (SELECT MAX(timestamp) FROM weather);
            """
            cursor.execute(request_str)
            result = cursor.fetchall()
            record_dict = {}
            for record in result:   #convert record into dictionary
                record_dict = {'timestamp': record[0],
                               'date':record[1],
                               'deviceid':record[2],
                               'temperature':record[3],
                               'windspeed':record[4],
                               'winddirection':record[5],
                               'humidity':record[6],
                               'pressure':record[7],
                               'aqi':record[8],
                               }
            return json.dumps(record_dict)  #Return json object with record


#####################################################
# Flask Routes
#####################################################

#database object for Flask routes
db = database('postgres://ntmlgtzglebvxt:7f29de081a06069389993e83b304eabc7a607ec4645a1fca7df79d5f167cf1e5@ec2-54-224-64-114.compute-1.amazonaws.com:5432/d2814k1j2ol13i',True)    #CHANGE TO FALSE IF NOT TEST

app = Flask(__name__)

#Test route
@app.route('/')
def hello_world():
    print(f"\nReceived request from {request.remote_addr}")
    print(f"Server is active")
    return 'Server is active'

#retrieve, insert, and delete all records by date and device
@app.route('/devicedata/all/<device_id>/<date>', methods = ['GET', 'POST', 'DELETE'])
def get(device_id,date):
    print(f"\nReceived request from {request.remote_addr}")
    if request.method == 'GET':
        print(f"Getting all records for device {device_id} on date {date}")
        return db.getday(device_id,date)
    if request.method == 'POST':
        data = request.get_json()
        db.insert("weather",data)
        print(f"Posted {data}")
        return "post_success"
    if request.method == 'DELETE':
        print(f"Deleting records for date {date}")
        db.delete("weather",date)
        return "delete_success"

#get record for each hour of a certain date and device
@app.route('/devicedata/hour/<device_id>/<date>', methods = ['GET'])
def hour(device_id, date):
    if request.method == 'GET':
        print("Getting hourly records for device " + device_id + " on date " + date)

#get latest record for certain device
@app.route('/devicedata/latest/<device_id>', methods = ['GET'])
def latest(device_id):
    print(f"\nReceived request from {request.remote_addr}")
    if request.method == 'GET':
        print("Getting most recent record for device " + device_id)
        record = db.getlatest(device_id)
        print(record)
        return record

#delete all route
@app.route('/devicedata/delete')
def delete():
    print(f"\nReceived request from {request.remote_addr}")
    db.delete("weather",None)
    return "delete_success"

if __name__ == '__main__':
    app.run()
