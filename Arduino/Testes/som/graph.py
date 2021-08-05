import serial
from time import sleep

ser = serial.Serial('/dev/ttyACM0')
ser.flushInput()

while True:
    valor = ser.readline()
    valor = str(valor).split('\'')[1][:-4]
    print(valor+10)
