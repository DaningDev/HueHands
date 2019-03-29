import serial
import json
import requests


# functions def

def getColor(cm) :
    return cm * 1310


# to find api on your network go to https://www.meethue.com/api/nupnp

body = {"devicetype":"jordo"}
res = requests.post("http://192.168.2.15/api", data=json.dumps(body))
print(res.content)
content = json.loads(res.content)

username = content[0]["success"]["username"]

body = {"hue": getColor(10) }
res = requests.put("http://192.168.2.15/api/" + username + "/lights/1/state",data=json.dumps(body))
print(res.content)

# init serial ports for connection with arduino
# ser = serial.Serial()
# ser.port = "COM3"
# ser.baudrate = 9600
# ser.open()


# # opens port of serial connection.
# print("reading....")
# while 1:
#     print(ser.readline(8))
    