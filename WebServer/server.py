import flask
from flask import Flask, request
import os
import sqlite3 as sl
from datetime import datetime
import time
import random
import os
import json

class database:
    def __init__(self,
                 name : str,
                 reset : bool = False):
        self.reset = reset
        self.db_filename = name +'.db'

        if reset:
            if os.path.exists(self.db_filename):
                os.remove(self.db_filename)

        db_con = sl.connect(self.db_filename)
        with db_con:
            db_con.execute("""
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

    def debug_print(self):
        db_con = sl.connect(self.db_filename)
        with db_con:
            cursor = db_con.cursor()
            cursor.execute("""SELECT * FROM weather WHERE date = \"2021_11_5\";""")
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
        db_con = sl.connect(self.db_filename)
        with db_con:
            db_cursor = db_con.cursor()
            request_str = """INSERT INTO {0} (timestamp, date, deviceid, temperature, windspeed, winddirection, humidity, pressure, aqi)
                VALUES( {1}, {2}, {3}, {4}, {5}, {6}, {7}, {8}, {9} );
                """.format("weather",
                           json_data["timestamp"],
                           '\''+json_data["date"]+'\'',
                           json_data["deviceid"],
                           json_data["temperature"],
                           json_data["windspeed"],
                           '\''+json_data["winddirection"]+'\'',
                           json_data["humidity"],
                           json_data["pressure"],
                           json_data["aqi"])
            db_con.execute(request_str)
            db_cursor.close()

    def delete(self,table,data):
        if table == "weather":
            if data is not None:
                self._weatherdelete(data)
            else:
                self._weatherdeleteall()

    def _weatherdelete(self,date):
        db_con = sl.connect(self.db_filename)
        with db_con:
            db_cursor = db_con.cursor()
            request_str = f"""
            DELETE FROM weather
            WHERE date = \'{date}\'"""
            db_cursor.execute(request_str)
            db_cursor.close()

    def _weatherdeleteall(self):
        db_con = sl.connect(self.db_filename)
        with db_con:
            db_cursor = db_con.cursor()
            request_str = "DELETE FROM weather;"
            db_cursor.execute(request_str)
            db_cursor.close()

    #return all records of a certain date and device
    def getday(self,deviceid,date : str):
        db_con = sl.connect(self.db_filename)
        result = 0
        with db_con:
            cursor = db_con.cursor()
            request_str = f"""SELECT * FROM weather 
            WHERE date = \"{date}\" AND deviceid = {deviceid}
            ORDER BY timestamp ASC;"""
            cursor.execute(request_str)
            result = cursor.fetchall()
        record_list = []
        for record in result:
            record_dict = {'timestamp':record[0],
                           'date':record[1],
                           'deviceid':record[2],
                           'temperature':record[3],
                           'windspeed':record[4],
                           'humidity':record[5],
                           'pressure':record[6],
                           'aqi':record[7],
                           }
            record_list.append(record_dict)
        #return flask.jsonify(json)
        return json.dumps(record_list)

    #return most recent record from a certain device
    def getlatest(self, deviceid):
        db_con = sl.connect(self.db_filename)
        with db_con:
            cursor = db_con.cursor()
            request_str = """SELECT * FROM weather
            WHERE timestamp = (SELECT MAX(timestamp) FROM weather);
            """
            cursor.execute(request_str)
            result = cursor.fetchall()
            record_dict = {}
            for record in result:
                record_dict = {'timestamp':record[0],
                               'date':record[1],
                               'deviceid':record[2],
                               'temperature':record[3],
                               'windspeed':record[4],
                               'humidity':record[5],
                               'pressure':record[6],
                               'aqi':record[7],
                               }
            return json.dumps(record_dict)


#####################################################
# Flask Routes
#####################################################

#database object for Flask routes
db = database('test',False)

app = Flask(__name__)
@app.route('/')
def hello_world():
    return 'hello test'

#retrieve, insert, and delete all records by date and device
@app.route('/devicedata/all/<device_id>/<date>', methods = ['GET', 'POST', 'DELETE'])
def get(device_id,date):
    if request.method == 'GET':
        print("Getting all records for device " + device_id + " on date " + date)
        return db.getday(device_id,date)
    if request.method == 'POST':
        print("posted")
        data = request.get_json()
        db.insert("weather",data)
        #db.debug_print()
        return "post_success"
    if request.method == 'DELETE':
        print("deleted")
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
    if request.method == 'GET':
        print("Getting most recent record for device " + device_id)
        record = db.getlatest(device_id)
        print(record)
        return record

#delete all route
@app.route('/devicedata/delete')
def delete():
    db.delete("weather")

if __name__ == '__main__':
    app.run()
