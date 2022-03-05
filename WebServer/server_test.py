#*************DESCRIPTION*************
#Written by Daniel Beeston
#sends requests to various paths on the server to ensure they are functioning correctly

import requests
from datetime import datetime

#HOST = https://flask-rews.herokuapp.com
HOST = "http://127.0.0.1:5000/"

def get_link(link : str):
    print(f"Getting {link}")

    try:
        req = requests.get(link)
        if len(str(req.content.decode())) > 200:
            print(str(req.content.decode())[:200] + " . . .")
        else:
            print(req.content.decode())

    except:
        print(f"Failed!")
    print("")


if __name__ == '__main__':
    t = datetime.now()
    current_timestamp = int(t.timestamp())
    d = str(t.date())
    d = d.replace('-','_')

    get_link(f"{HOST}/devicedata/all/0/{d}")

    get_link(f"{HOST}/devicedata/sensor/temperature/0/{d}")
    get_link(f"{HOST}/devicedata/sensor/pressure/0/{d}")
    get_link(f"{HOST}/devicedata/sensor/windspeed/0/{d}")

    get_link(f"{HOST}/devicedata/stats/temperature/0/{d}")
    get_link(f"{HOST}/devicedata/stats/pressure/0/{d}")
    get_link(f"{HOST}/devicedata/stats/windspeed/0/{d}")

    get_link(f"{HOST}/devicedata/latest/0")
