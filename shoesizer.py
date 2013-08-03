#!/usr/bin/python

import serial
import os
from math import cos, sqrt, radians

BASE_ANGLE = 19
arm = 34.0
BASE_DIST = 11.0

def calc_size(angle):
    angle += BASE_ANGLE

    length = sqrt(arm**2 + arm**2 - 2*arm*arm*cos(radians(angle))) #c = sqrt(a^2 + b^2 - 2*a*b*cos(angle))
    size = (3.0/2) * (length + 2) #http://en.wikipedia.org/wiki/Shoe_size#Europe
    return size


ser = serial.Serial("/dev/ttyUSB1")  # open first serial port
print ser.portstr       # check which port was really used
try:
    line = ""
    while True:
        try:
            newLine = ser.readline()
            if newLine[3:] != line[3:]:
                print newLine
                line = newLine
                if "ObjectHit" in line:
                    parts = line.split(" ")
                    angleStr = parts[0]
                    angle = int(angleStr)
                    size = int(calc_size(angle))
                    text = "'your size is {0}'".format(size)
                    print text
                    os.system("echo '{0}' | festival --tts".format(text))

                    #ser.write("start\n")
        except KeyboardInterrupt:
            break
finally:
    print "Closing"
    ser.close()