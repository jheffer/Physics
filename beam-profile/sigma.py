#!/usr/bin/python

import sys

# Read data to 2D array
file = open(sys.argv[1], "r")
data = []
for line in file:
  if(line.strip()[0] != "#"):
    data.append(float(line.strip().split("\t")[1]))

# background subtract
bg = (data[0]+data[1]+data[3]+data[-1]+data[-2]+data[-3])/6
for i,value in enumerate(data):
  data[i] = value - bg

# Find maximum pixel position
max = -1
for x,value in enumerate(data):
  if(value > max):
    peakpos = x
    max = value

# moving right
sigma = -1
for x,value in enumerate(data):
  if(x >= peakpos):
    if(value < max*0.36787944117):
      sigma = x - peakpos
      break

# if fail, try moving right
if sigma==-1:
  for x,value in enumerate(reversed(data)):
    if(x < peakpos):
      if (value < max*0.36787944117):
        sigma = x - peakpos
        break

print sigma
