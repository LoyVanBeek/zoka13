#!/usr/bin/python

import serial
import os

ser = serial.Serial("/dev/ttyUSB1")  # open first serial port
print ser.portstr       # check which port was really used

try:
    line = ""
    while True:
        try:
            newLine = ser.readline()
            print newLine
            if newLine != line:
                line = newLine
                if "ObjectHit" in line:
                    parts = line.split(" ")
                    angleStr = parts[0]
                    angle = int(angleStr)

                    os.system("echo 'your size is {0}' | festival --tts".format(angle))

                    ser.write("start\n")
        except KeyboardInterrupt:
            break
finally:
    print "Closing"
    ser.close()