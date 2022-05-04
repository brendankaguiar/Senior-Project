Details regarding server.py paths


Host:
https://flask-rews.herokuapp.com

=======================
GET Paths:
=======================

*************GET ALL RECORDS*****************

/devicedata/all/<device_id>/<date>
	--returns json list of objects with all sensor data
	--returns all records on <date>

/devicedata/all/<device_id>/<date>/<hour>
	--returns json list of objects with all sensor data
	--returns records on <date> at hour <hour>

*************GET SENSOR RECORDS*****************

/devicedata/sensor/<sensor>/<device_id>/<date>
	--returns json list of objects with data of only one sensor
	--returns all records on <date>

/devicedata/sensor/<sensor>/<device_id>/<date>/<hour>
    --returns json list of objects with data of only one sensor
    --returns records on <date> at hour <hour>

*************GET STATS*****************

/devicedata/stats/<sensor>/<device_id>/<date>
    --returns json object of format {min,max,average}
    --does not work with wind direction

*************GET LOCATION**************
/devicedata/metadata/location/<device_id>
	--returns json object of format {location, lastupdated, city}

*************GET LATEST RECORD*****************

/devicedata/latest/<device_id>
	--gets latest record in database

/devicedata/delete
	--delete all data in database

=======================
POST Paths:
=======================

********POST WEATHER DATA************

/devicedata/all/<device_id>/<date>
	--Used only on Raspberry PI
	--include JSON object in request data

<sensor> : "temperature", "windspeed", "winddirection", "humidity", "aqi", "pressure"
<device_id> : int- device id in database
<date> : takes the form <year>_<month>_<day>, examples: 2022_02_16, 2022_03_01, 2022_10_24
<hour> : int, hour of the day, from 0 to 23


********POST LOCATION***************
/devicedata/metadata/<device_id>
	--used only in Raspberry pi
	--include JSON object in request body
<device_id> : int- device id in database


Example link:
https://flask-rews.herokuapp.com/devicedata/sensor/pressure/0/2022_02_16
	-- gets pressure data for device 0 on date 2022_02_16
