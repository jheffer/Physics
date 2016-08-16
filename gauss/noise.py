# -*- coding: utf-8 -*-
import re
import sys
import math

####################    Settings     ######################

N_std = 3 # number of standard deviations

####################    Open frames     ######################

filename = str(sys.argv[1]).strip()
with open(filename,'r') as f:
  content = f.readlines()
frames = []
for line in content:
   frames.append(re.split("\t| ", line.strip())) # split each line

# Convert strings to integers
for i,frame in enumerate(frames):
    frames[i][0] = int(frame[0])
    frames[i][1] = float(frame[1]) # normalised brightness
    frames[i][2] = int(frame[2])

####################     Mean +/- sigma     ######################

# mean and variance pre-drop
sum = 0.0
for frame in frames:
  sum += frame[1]
mean = sum / len(frames)

varsum = 0.0
for frame in frames:
  varsum += pow(frame[1] - mean, 2)
var = varsum / len(frames)
sig = math.sqrt(var)

####################     Is it noise?     ######################

if sig/mean > 0.2:
  print "0"
else:
  print "1"
