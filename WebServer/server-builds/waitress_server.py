#*************DESCRIPTION*************
#Written by Daniel Beeston
#Flask deployment server
#Run using "python waitress_server.py <IP>:<Port>"
#Running without arguments will run on localhost port 5000

#External packages used: waitress, sys

from waitress import serve
import server
import sys

#Serve by default on localhost on port 5000
server_host = "127.0.0.1"
server_port = 5000

#check number of arguments and determine if argv[1] is a valid IP
if len(sys.argv) != 1:
    ip = sys.argv[1]
    ip = ip.split(':')
    if len(ip)!=2:  #check if valid IP format
        print("Please enter valid ip of format <host>:<port>")
        exit(-1)
    server_host = ip[0]
    server_port = ip[1]

print(f"Serving on {server_host}:{server_port}\nCtrl+C to exit")
#attempt to serve on chosen host/port
try:
    serve(server.app,host=server_host,port=server_port)
#Exit if <IP>:<Port> is invalid
except:
    print(f"Unable to host server on {server_host}:{server_port}")
    exit(-1)
