#!/usr/bin/python

import sys
import os

# return highest pixel value in an array

# Read data to 2D array
file = open(sys.argv[1], "r")
data = []
for line in file:
  if(line.strip()[0] != "#"):
    data.append(float(line.strip().split("\t")[1]))

peakpos = -1
max = -1
for x,value in enumerate(data):
  if(value > max):
    max = value
    peakpos = x

print peakpos
