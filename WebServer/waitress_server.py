from waitress import serve
import server
import sys

server_host = "127.0.0.1"
server_port = 5000

if len(sys.argv) != 1:
    ip = sys.argv[1]
    ip = ip.split(':')
    if len(ip)!=2:
        print("Please enter valid ip of format <host>:<port>")
        exit(-1)
    server_host = ip[0]
    server_port = ip[1]

print(f"Serving on {server_host}:{server_port}\nCtrl+C to exit")
try:
    serve(server.app,host=server_host,port=server_port)
except:
    print(f"Unable to host server on {server_host}:{server_port}")
    exit(-1)
