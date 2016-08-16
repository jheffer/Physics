# -*- coding: utf-8 -*-
import re
import sys
import math

####################    Settings     ###########################

nSigDrop = 150 # number of standard deviations for drop frame
nSigRise = 250
nSigZero = 10
scan = 3 # number of preceding frames to analyse

####################    Functions     ###########################

def mean(l):
   "Returns mean of a list of numbers"
   return sum(l)/float(len(l));

def stdev(l):
   "Returns standard deviation of a list of numbers"
   sum = 0
   u = mean(l)
   for x in l:
     sum += pow(x-u, 2)
   return math.sqrt(sum/len(l));

####################    Open data     ###########################

filename = str(sys.argv[1]).strip()
with open(filename,'r') as f:
  content = f.readlines()
frames = []
for line in content:
   frames.append(re.split("\t| ", line.strip())) # split each line

# Convert strings to integers
for i,frame in enumerate(frames):
    frames[i][0] = int(frame[0])
    frames[i][1] = int(frame[1]) # normalised brightness
    frames[i][2] = int(frame[2])

####################     Drop frame     ##########################
# take a moving mean +/- sigma, drop frame when falls below n sig

dropFrame = -1
for i,frame in enumerate(frames):
  if i > scan and i < len(frames)-(scan):
    prevFrames = [] # list of previous frame values (including current frame)
    for n in range(0, scan):
      prevFrames.append(frames[i-n][1])
    nextFrames = [] # list of subsequent frame values
    for n in range(1, scan+1):
      nextFrames.append(frames[i+n][1])
    # compare subsequent frame value to moving average
    fall = (mean(prevFrames) - mean(nextFrames))/stdev(prevFrames) # how much does it fall?
    #print str(frame[0])+"\t"+str(frame[1])+"\t"+str(round(mean(prevFrames),1))+"\t"+str(round(mean(nextFrames),1))+"\t"+str(round(stdev(prevFrames),1))+"\t"+str(round(fall,1))
    if fall > nSigDrop: # if it drops significantly
      dropFrame = frame[0] # set the drop frame
      break # quit the loop

####################     Rise frame     ##########################
# First "rise" from end of data (end of flash peak)

riseFrame = -1
# move backwards from end,  moving mean +/- sigma, highest peak
for i,frame in enumerate(reversed(frames)):
  if i > scan and i < (len(frames)-scan) and frame[0] > dropFrame:
    prevFrames = [] # list of previous frame values (including current frame)
    for n in range(0, scan):
      prevFrames.append(frames[len(frames)-(i-n)][1])
    nextFrames = [] # list of subsequent frame values
    for n in range(1, scan+1):
      nextFrames.append(frames[len(frames)-(i+n)][1])
    # compare subsequent frame value to moving average
    rise = (mean(nextFrames) - mean(prevFrames))/stdev(prevFrames) # measure rise
    #print str(frame[0])+"\t"+str(frame[1])+"\t"+str(round(mean(nextFrames),1))+"\t"+str(round(mean(prevFrames),1))+"\t"+str(round(stdev(prevFrames),1))+"\t"+str(round(rise,1))
    if rise > nSigRise:
      riseFrame = frame[0]
      break

####################     Flash frame     ##########################
# find peak, assuming narrow peaks

flashFrame = -1
for i,frame in enumerate(frames):
  if i > scan and i < (len(frames)-scan) and frame[0] > dropFrame and frame[0] < riseFrame:
    prevFrames = [] # previous frame values
    for n in range(1, scan+1):
      prevFrames.append(frames[i-n][1])
    nextFrames = [] # subsequent frame values
    for n in range(1, scan+1):
      nextFrames.append(frames[i+n][1])
    if frame[1]/mean(prevFrames) > 2 and frame[1]/mean(nextFrames) > 2:
      flashFrame = frame[0]

####################     Zero frame     ##########################
# edge detect (fall) between drop and peak

zeroFrame = -1
for i,frame in enumerate(frames):
  if i > scan and i < (len(frames)-scan) and frame[0] > dropFrame and frame[0] < flashFrame:
    prevFrames = [] # previous frame values
    for n in range(1, scan+1):
      prevFrames.append(frames[i-n][1])
    nextFrames = [] # subsequent frame values (including current frame)
    for n in range(0, scan):
      nextFrames.append(frames[i+n][1])
    edge = (mean(prevFrames)-mean(nextFrames)) / stdev(nextFrames)
    if edge > nSigZero:
      zeroFrame = frame[0]
      break;

####################     Data properties     ##########################

# Find average of high region before drop
highData = []
for frame in frames:
  if frame[0] < dropFrame:
    highData.append(frame[1])
meanPreDrop = mean(highData)
sigPreDrop = stdev(highData)

# Find average of low region after flash
lowData = []
for frame in frames:
  if frame[0] > riseFrame:
    lowData.append(frame[1])
meanPostFlash = mean(lowData)
sigPostFlash = stdev(lowData)

####################     Print result     ######################

#print "Drop = "+str(dropFrame)
#print "Zero = "+str(zeroFrame)
#print "Flash = "+str(flashFrame)
#print "Rise = "+str(riseFrame)
#print "Pre-drop mean = "+str(round(meanPreDrop,1))+" +/- "+str(round(sigPreDrop,1))
#print "Post-flash mean = "+str(round(meanPostFlash,1))+" +/- "+str(round(sigPostFlash,1))

# command line arguments
if len(sys.argv) > 2:
  output = str(sys.argv[2]).strip() # choose what number to spit out
else:
  output = ""

# write to screen
if output == "1":
  print dropFrame
elif output == "2":
  print zeroFrame
elif output == "3":
  print flashFrame
elif output == "4":
  print riseFrame
else:
  print "No output specified"
