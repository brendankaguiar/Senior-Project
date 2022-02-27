Host:
https://flask-rews.herokuapp.com

GET Paths:
/devicedata/all/<device_id>/<date>
	--returns json list of objects with all sensor data

/devicedata/sensor/<sensor>/<device_id>/<date>
	--returns json list of objects with data of only one sensor

/devicedata/latest/<device_id>
	--gets latest record in database

/devicedata/delete
	--delete all data in database


POST Path:
/devicedata/all/<device_id>/<date>
	--Used only on Raspberry PI
	--include JSON object in request data


<sensor> : "temperature", "windspeed", "winddirection", "humidity", "aqi", "pressure"
<device_id> : int (just use 0)
<date> : takes the form <year>_<month>_<day>, examples: 2022_02_16, 2022_03_01, 2022_10_24




Example link:
https://flask-rews.herokuapp.com/devicedata/sensor/pressure/0/2022_02_16
	-- gets pressure data for device 0 on date 2022_02_16