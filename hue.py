import serial
import json
import requests


body = {"devicetype":"jordo"}
r = requests.post("http://145.49.34.222/api", data=json.dumps(body))
print(r.content)
content = json.loads(r.content)
print(content["succes"]["username"])


# init serial ports for connection with arduino
ser = serial.Serial()
ser.port = "COM3"
ser.baudrate = 9600
ser.open()


# opens port of serial connection.
print("reading....")
while 1:
    print(ser.readline(8))
    