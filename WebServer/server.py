#*************DESCRIPTION*************
#Written by Daniel Beeston
#Flask server routes and database functions
#Run using "python server.py" to host development server on 127.0.0.1

#External packages used: Flask, sqlite3, os, json, datetime

from flask import Flask, request
import psycopg2
from datetime import datetime
import urllib.parse as urlparse
import random
import math
import json
import geopy

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
            CREATE TABLE IF NOT EXISTS device (
                deviceid INT PRIMARY KEY,
                location TEXT,
                batterylevel INT,
                lastupdated INT
            );
            """)

            db_cursor.execute("""
            CREATE TABLE IF NOT EXISTS weather (
                id SERIAL PRIMARY KEY,
                timestamp INT,
                date TEXT,
                deviceid INT,
                temperature REAL,
                windspeed REAL,
                winddirection TEXT,
                humidity REAL,
                pressure REAL,
                aqi REAL,
                time TIME,
                CONSTRAINT deviceid_fk
                    FOREIGN KEY(deviceid) 
                    REFERENCES device(deviceid)
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

    def debug_generatedata(self,days : int):
        hours = 24*days

        db_con = psycopg2.connect(
            dbname=self.dbname,
            user=self.user,
            password=self.password,
            host=self.host,
            port=self.port
        )
        with db_con:
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

            db_cursor = db_con.cursor()

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
                    request_str = """INSERT INTO {0} (timestamp, date, deviceid, temperature, windspeed, winddirection, humidity, pressure, aqi)
                                VALUES( {1}, {2}, {3}, {4}, {5}, {6}, {7}, {8}, {9} );
                                """.format("weather",
                                           str(current_timestamp),
                                           '\''+d+'\'',
                                           0,
                                           str(round(temp,3)),
                                           str(round(wind_speed,3)),
                                           '\''+current_wind+'\'',
                                           str(humidity),
                                           str(round(pressure,3)),
                                           str(aqi))
                    db_cursor.execute(request_str)
                    #result = db_cursor.fetchall()
                    #print(request_str)
                    #print(f"insterted record timestamp {current_timestamp}")
                except: #print error if post failed
                    print(f"Error Posting {current_timestamp}")
                current_timestamp+=300
            db_cursor.close()
            print("Debug data successfully generated")



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

    def weatherdeletedate(self,date):
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

    def weatherdeleteall(self):
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

    def weatherdeletedevice(self,device_id):
        db_con = psycopg2.connect(
            dbname=self.dbname,
            user=self.user,
            password=self.password,
            host=self.host,
            port=self.port
        )
        with db_con:
            db_cursor = db_con.cursor()
            try:
                request_str = f"""DELETE FROM weather 
                                 WHERE deviceid = {device_id};"""
                db_cursor.execute(request_str)
            except:
                db_cursor.close()
                return False
            db_cursor.close()
            return True


    #return all records of a certain date and device
    def getday(self,deviceid,date : str, hour : int):
        db_con = psycopg2.connect(
            dbname=self.dbname,
            user=self.user,
            password=self.password,
            host=self.host,
            port=self.port
        )
        result = None
        with db_con:    #open db_con and retrieve records
            cursor = db_con.cursor()
            request_str = f"""SELECT * FROM weather 
            WHERE date = (%s) AND deviceid = {deviceid}
            ORDER BY timestamp ASC;"""
            cursor.execute(request_str,[date])
            result = cursor.fetchall()
        record_list = []
        temp_list = []

        #if hour >= 0 and hour <= 23:    #if hour is valid
        #    for record in result:
        #        if datetime.fromtimestamp(record[0])
        #
        #    result = temp_list


        for record in result:   #convert records into dictionary
            record_dict = {'timestamp':record[1],
                           'date':record[2],
                           'deviceid':record[3],
                           'temperature':record[4],
                           'windspeed':record[5],
                           'winddirection':record[6],
                           'humidity':record[7],
                           'pressure':record[8],
                           'aqi':record[9],
                           }
            #print(record_dict)
            record_list.append(record_dict)
        #return flask.jsonify(json)
        return json.dumps(record_list)  #Return json object array with records

    #return only <sensor> records with timestamp, date, and id
    def getsensor(self,deviceid,date,sensor):
        db_con = psycopg2.connect(
            dbname=self.dbname,
            user=self.user,
            password=self.password,
            host=self.host,
            port=self.port
        )
        result = None
        with db_con:    #open db_con and retrieve records
            cursor = db_con.cursor()
            request_str = f"""SELECT timestamp, date, deviceid, {sensor} FROM weather 
            WHERE date = (%s) AND deviceid = {deviceid}
            ORDER BY timestamp ASC;"""
            cursor.execute(request_str,[date])
            result = cursor.fetchall()
        record_list = []
        for record in result:   #convert records into dictionary
            record_dict = {'timestamp':record[0],
                           'date':record[1],
                           'deviceid':record[2],
                           sensor:record[3],
                           }
            record_list.append(record_dict)
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
            request_str = f"""SELECT * FROM weather
            WHERE timestamp = (SELECT MAX(timestamp) FROM weather) AND deviceid = {deviceid};
            """
            cursor.execute(request_str)
            result = cursor.fetchall()
            record_dict = {}
            for record in result:   #convert record into dictionary
                record_dict = {'timestamp': record[1],
                               'date':record[2],
                               'deviceid':record[3],
                               'temperature':record[4],
                               'windspeed':record[5],
                               'winddirection':record[6],
                               'humidity':record[7],
                               'pressure':record[8],
                               'aqi':record[9],
                               }
            record_list = []
            record_list.append(record_dict)
            return json.dumps(record_list)  #Return json object with record

    def registerdevice(self, deviceid):
        db_con = psycopg2.connect(
            dbname=self.dbname,
            user=self.user,
            password=self.password,
            host=self.host,
            port=self.port
        )
        with db_con:
            try:
                cursor = db_con.cursor()
                request_str = f"""SELECT deviceid FROM device
                WHERE deviceid = {deviceid};
                """
                cursor.execute(request_str)
                result = cursor.fetchall()
                if len(result) != 0:
                    return "device_already_exists"
                request_str = f"""INSERT INTO device (deviceid) VALUES({deviceid})"""
                cursor.execute(request_str)
            except:
                return "register_failed"

            return "register_success"

    #deletes device and all its data
    def deletedevice(self, deviceid):
        if not self.weatherdeletedevice(deviceid):  #delete device data from weather table
            return "delete_failed"

        db_con = psycopg2.connect(
             dbname=self.dbname,
            user=self.user,
            password=self.password,
            host=self.host,
            port=self.port)

        with db_con:    #delete device from device table
            try:
                cursor = db_con.cursor()
                request_str = f"""DELETE FROM device 
                                 WHERE deviceid = {deviceid};"""
                cursor.execute(request_str)
            except:
                return "delete_failed"
        return "delete_success"

    #return json object with min, max, avg stats of <sensor> on <date>
    def getstats(self,deviceid,date,sensor):
        if sensor!="temperature" and sensor!="windspeed" and sensor!="humidity" and sensor!="pressure" and sensor!="aqi":
            return ""

        db_con = psycopg2.connect(
            dbname=self.dbname,
            user=self.user,
            password=self.password,
            host=self.host,
            port=self.port
        )
        result = None
        with db_con:    #open db_con and retrieve records
            cursor = db_con.cursor()
            request_str = f"""SELECT MIN({sensor}), MAX({sensor}), AVG({sensor}) FROM weather 
            WHERE date = (%s) AND deviceid = {deviceid};"""
            cursor.execute(request_str,[date])
            result = cursor.fetchall()
            result = result[0]

        record_dict = { 'min':result[0],
                        'max':result[1],
                        'average':result[2]
                      }
        record_list = []
        record_list.append(record_dict)

        return json.dumps(record_list)  #Return json object array with records

    def updatedevice(self,deviceid,json_data):
        db_con = psycopg2.connect(
            dbname=self.dbname,
            user=self.user,
            password=self.password,
            host=self.host,
            port=self.port
        )
        with db_con:
            try:
                db_cursor = db_con.cursor()
                request_str = f"""UPDATE device SET location = \'{json_data["location"]}\', lastupdated = \'{int(json_data["lastupdated"])}\'
                            WHERE deviceid = {deviceid};
                            """
                db_cursor.execute(request_str)
                db_cursor.close()
            except:
                return "update_failed"
        return "update_success"

    def getlocation(self,deviceid):
        db_con = psycopg2.connect(
            dbname=self.dbname,
            user=self.user,
            password=self.password,
            host=self.host,
            port=self.port
        )
        result = None
        try:
            with db_con:    #open db_con and retrieve records
                cursor = db_con.cursor()
                request_str = f"""SELECT location, lastupdated FROM device 
                WHERE deviceid = {deviceid};"""

                cursor.execute(request_str)
                result = cursor.fetchall()
            record_list = []

            location = result[0][0].split(",")
            lat = [location[0][0:location[0].find(".") - 2],location[0][location[0].find(".") - 2:len(location[0])]]
            location[0] = round(float(lat[0]) + float(lat[1])/60,5)
            long = [location[2][0:location[2].find(".") - 2],location[2][location[2].find(".") - 2:len(location[2])]]
            location[2] = round(float(long[0]) + float(long[1])/60,5)

            if location[1] == 'S':
                location[0] *= -1
            if location[3] == 'W':
                location[2] *= -1

            dec_location = str(location[0])+', '+str(location[2])

            geolocator = geopy.Nominatim(user_agent="rews")
            location = geolocator.reverse(geopy.Point(dec_location))

            if "city" in location.raw['address']:
                city = location.raw['address']['city'] + ", " + location.raw['address']['state']
            else:
                city = location.raw['address']['county'] + ", " + location.raw['address']['state']


            record_list.append({'location':dec_location, 'lastupdated':result[0][1], 'city':city})

            return json.dumps(record_list)  #Return json object array with records
        except:
            return "failed"




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
        return db.getday(device_id,date,-1)
    if request.method == 'POST':
        data = request.get_json()
        db.insert("weather",data)
        print(f"Posted {data}")
        return "post_success"
    if request.method == 'DELETE':
        print(f"Deleting records for date {date}")
        db.weatherdeletedate(date)
        return "delete_success"

#get all records for certain device, only return <sensor> along with timestamp, date, deviceid
@app.route('/devicedata/sensor/<sensor>/<device_id>/<date>', methods = ['GET'])
def getsensor(sensor,device_id,date):
    print(f"\nReceived request from {request.remote_addr}")
    if request.method == 'GET':
        print(f"Getting {sensor} records for device {device_id} on date {date}")
    if sensor == "temperature" or sensor == "windspeed" or sensor == "winddirection" or sensor == "humidity" or sensor == "pressure" or sensor == "aqi":
        return db.getsensor(device_id,date,sensor)
    return "invalid_sensor"


#get record for an hour of a certain date and device
@app.route('/devicedata/all/<device_id>/<date>/<hour>', methods = ['GET'])
def hour(device_id, date, hour):
    print(f"\nReceived request from {request.remote_addr}")
    if request.method == 'GET':
        print("Getting hourly records for device " + device_id + " on date " + date)
        return db.getday(device_id,date,hour)

#get all records for <device_id> on date <date> and hour <hour>, only return <sensor> along with timestamp, date, deviceid
@app.route('/devicedata/sensor/<sensor>/<device_id>/<date>/<hour>', methods = ['GET'])
def getsensorhour(sensor, device_id, date, hour):
    print(f"\nReceived request from {request.remote_addr}")
    if request.method == 'GET':
        print(f"Getting {sensor} records for device {device_id} on date {date}, hour {hour}")
    if sensor == "temperature" or sensor == "windspeed" or sensor == "winddirection" or sensor == "humidity" or sensor == "pressure" or sensor == "aqi":
        return db.getsensor(device_id,date,sensor)
    return "invalid_sensor"



#get latest record for certain device
@app.route('/devicedata/latest/<device_id>', methods = ['GET'])
def latest(device_id):
    print(f"\nReceived request from {request.remote_addr}")
    if request.method == 'GET':
        print("Getting most recent record for device " + device_id)
        record = db.getlatest(device_id)
        print(record)
        return record

#get min, max, avg values for <sensor> for device <device> on <date>
@app.route('/devicedata/stats/<sensor>/<device_id>/<date>', methods = ['GET'])
def stats(sensor, device_id, date):
    print(f"\nReceived request from {request.remote_addr}")
    if request.method == 'GET':
        print(f"Getting min/max/average {sensor} for device " + device_id + " on date " + date)
        return db.getstats(device_id,date,sensor)

#delete all route, deletes all tuples in database
@app.route('/devicedata/delete')
def delete():
    print(f"\nReceived request from {request.remote_addr}")
    db.weatherdeleteall()
    return "delete_success"

#delete all records for <device_id>
@app.route('/devicedata/delete/<device_id>')
def delete_device(device_id):
    print(f"\nReceived request from {request.remote_addr}")
    print(f"Delete all records for device {device_id}")
    result = db.weatherdeletedevice(device_id)
    if result:
        return "delete_success"
    return "delete_fail"


@app.route('/devicedata/register/<device_id>')
def register(device_id):
    print(f"\nReceived request from {request.remote_addr}")
    print(f"Attempting to register device {device_id}")
    return db.registerdevice(device_id)

@app.route('/devicedata/unregister/<device_id>')
def unregister(device_id):
    print(f"\nReceived request from {request.remote_addr}")
    print(f"Attempting to unregister device {device_id}")
    return db.deletedevice(device_id)

@app.route('/devicedata/metadata/<device_id>', methods=['POST'])
def metadata(device_id):
    data = request.get_json()
    print(f"\nReceived request from {request.remote_addr}")
    print(f"Updating metadata for {device_id}")
    json_data = request.get_json()
    return db.updatedevice(device_id,json_data)

@app.route('/devicedata/metadata/location/<device_id>', methods=['GET'])
def locationdata(device_id):
    print(f"\nReceived request from {request.remote_addr}")
    print(f"Returning location metadata for {device_id}")
    return db.getlocation(device_id)


@app.route('/debug/generate_data/<days>')
def debug_generatedata(days):
    print(f"\nReceived request from {request.remote_addr}")
    try:
        d = int(days)
    except:
        return "invalid request!"

    db.debug_generatedata(d)
    return f"inserted {d} days of test data"

if __name__ == '__main__':
    app.run()
