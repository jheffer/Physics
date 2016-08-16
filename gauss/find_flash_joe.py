# -*- coding: utf-8 -*-
import re # regular expression for splitting via "\t" and " "
import sys
import math

# Find the flash frame in brightness data
# Data format: frame_num sum_brightness N_above_threshold

# Load data from text file
filename = str(sys.argv[1]).strip()
with open(filename) as f:
  content = f.readlines()

# Read text file to 2D array of data (3 columns)
data = []
for line in content:
   data.append(re.split("\t| ", line.strip())) # split each line

# Convert strings to integers
for i,line in enumerate(data):
  for j,item in enumerate(line):
    data[i][j] = int(item)

#  Find brightest frame
max = -1
for frame in data:
  if frame[1] > max:
    max = frame[1]

# Find drop
compare = 0
# (Warning: i is list item number, which may be different to frame number)
for i,frame in enumerate(data): # Compare to next frame
  if frame[0] != data[-1][0]: # if not last item in list
    nextFrame = data[i+1]
    if( (frame[1] - nextFrame[1]) > compare):
      compare = frame[1] - nextFrame[1]
      dropFrame = nextFrame[0]

#print "Drop frame = " + str(dropFrame)

# mean and variance pre-drop
sumPreDrop = 0.0
for frame in data:
  if frame[0] <= dropFrame:
    sumPreDrop += frame[1]
NpreDrop = dropFrame - data[0][0] # number of frames before the drop
meanPreDrop = sumPreDrop / NpreDrop
varSumPreDrop = 0.0
for frame in data:
  if frame[0] <= dropFrame:
    varSumPreDrop += (frame[1] - meanPreDrop)*(frame[1] - meanPreDrop)
varPreDrop = varSumPreDrop / NpreDrop

# mean and variance post-drop
sumPostDrop = 0.0
for frame in data:
  if frame[0] > dropFrame:
    sumPostDrop += frame[1]
NpostDrop = data[-1][0] - dropFrame # number of frames before the drop
meanPostDrop = sumPostDrop / NpostDrop
varSumPostDrop = 0.0
for frame in data:
  if frame[0] > dropFrame:
    varSumPostDrop += (frame[1] - meanPostDrop)*(frame[1] - meanPostDrop)
varPostDrop = varSumPostDrop / NpostDrop

#print "Mean pre-drop = " + str(round(meanPreDrop,1)) + " +/- " + str(round(math.sqrt(varPreDrop),1))
#print "Mean post-drop = " + str(round(meanPostDrop,1)) + " +/- " + str(round(math.sqrt(varPostDrop),1))

# clearance
# ...

# check if data is noise/unuseable
# ...

peakFrame = 0
peakFrameValue = 0
# Find flash frame
for frame in data:
  if frame[0] > dropFrame:
    # find peak highest above mean + std 
    if frame[0] > peakFrameValue:
      peakFrame = frame[0]
      peakFrameValue = frame[1]

#print "Flash frame number = " + str(peakFrame)
#print "Flash frame value = " + str(peakFrameValue)
print str(peakFrame)
