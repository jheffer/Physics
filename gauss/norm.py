#!/usr/bin/env python
import re # regular expression for splitting via "\t" and " "
import sys

# Load data from text file
filename = str(sys.argv[1]).strip()
with open(filename) as f:
  content = f.readlines()

# Read text file to 2D array of data (3 columns)
data = []
for line in content:
   data.append(re.split("\t| ", line.strip())) # split each line using reg. exp.

# Convert strings to integers
for i,frame in enumerate(data):
    data[i][0] = int(frame[0])
    data[i][1] = float(frame[1])
    data[i][2] = int(frame[2])

maxVal = 0
# find brightest frame
for frame in data:
  if frame[1] > maxVal:
    maxVal = frame[1]
    maxNo = frame[0] # record frame number

# normalise
for i,frame in enumerate(data):
  data[i][1] = frame[1]/maxVal

# print results
for frame in data:
  print str(frame[0]) + "\t" + str(frame[1]) + "\t" + str(frame[2])
