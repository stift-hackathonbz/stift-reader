import serial
import requests

ser = serial.Serial('/dev/ttyACM0', 115200, timeout=1)

while True: 
   line = ser.readline()   # read a '\n' terminated line
   if len(line)>4:
      line = line[:7]
      print(line)
      requests.post("https://stift-server.herokuapp.com/api/rfid/"+line)
