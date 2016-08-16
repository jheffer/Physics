# -*- coding: utf-8 -*-
import re
import sys
import math

####################    Settings     ######################

N_std = 40 # number of standard deviations
clearance = 10 # clearance from drop
if len(sys.argv) > 2:
  output = str(sys.argv[2]).strip() # choose what number to spit out
else:
  output = "1"

####################    Open data     ######################

filename = str(sys.argv[1]).strip()
with open(filename,'r') as f:
  content = f.readlines()
frames = []
for line in content:
   frames.append(re.split("\t| ", line.strip())) # split each line

# Convert strings to integers
for frame in frames:
  frame[0] = int(frame[0])
  frame[1] = float(frame[1]) # normalised brightness

####################     Smooth    ######################

# Smooth
for i,frame in enumerate(frames):
  if frame[0] != frames[-1][0]: # if not last frame
    frame[1] = 0.5*(frame[1] + frames[i+1][1]) # average w/ following frame
  if frame[0] == frames[-1][0]: # if last frame
    frame[1] = 0.5*(frame[1] + frames[0][1]) # average w/ first frame

# print data
for frame in frames:
  print str(frame[0]) + "\t" + str(frame[1])
