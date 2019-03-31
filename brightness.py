import serial
import json
import requests
import struct
import math



# to find api on your network go to https://www.meethue.com/api/nupnp

body = {"devicetype":"jordo"}

# hardcodes ip adress
res = requests.post("http://192.168.2.15/api", data=json.dumps(body))
print(res.content)
content = json.loads(res.content)

username = content[0]["success"]["username"]

# init serial ports for connection with arduino
ser = serial.Serial()
ser.port = "COM8"
ser.baudrate = 9600
ser.xonxoff = 0
ser.open()

 # opens port of serial connection.
print("reading....")
values = None


# functions def

def getBrightness(cm) :
    print(cm)
    body = {"bri": math.floor(cm * 5)  }
    res = requests.put("http://192.168.2.15/api/" + username + "/lights/1/state",data=json.dumps(body))
    print(res.content)


while 1:
    values = ser.readline()
    text = values[1:]
    try:
        value = None
        getBrightness(float(text))
    except:
        print(text)
        