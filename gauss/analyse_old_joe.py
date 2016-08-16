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
for i,frame in enumerate(frames):
    frames[i][0] = int(frame[0])
    frames[i][1] = int(frame[1]) # normalised brightness
    frames[i][2] = int(frame[2])

####################     Drop frame     ##########################
# take a moving mean +/- sigma, drop frame when falls below n sig

meanPrev = 0 # mean of preceding frames
nPrev = 3 # number of preceding frames to analyse
for i,frame in enumerate(frames):
  for n in range(1, nPrev):
    meanPrev += frames[i-n][1]
  print str(frame[0])+"\t"+str()

#print "Drop:\t" + str(dropFrame)

####################     Mean +/- sigma     ######################

# mean
sumPostDrop = 0.0
NpostDrop = 0
for frame in frames:
  if frame[0] > dropFrame + clearance:
    sumPostDrop += frame[1]
    NpostDrop += 1 # count number of frames
if NpostDrop > 0:
  meanPostDrop = sumPostDrop / NpostDrop
else:
  meanPostDrop = -1

# variance
varSumPostDrop = 0.0
for frame in frames:
  if frame[0] > dropFrame + clearance:
    varSumPostDrop += (frame[1] - meanPostDrop)*(frame[1] - meanPostDrop)
if NpostDrop > 0:
  varPostDrop = varSumPostDrop / NpostDrop
  stDev = math.sqrt(varPostDrop)
else:
  varPostDrop = -1
  stDev = -1

#print "Post-drop mean:\t" + str(meanPostDrop) + " +/- " + str(stDev)


####################     Lasers off     ######################

for frame in frames:
  if (frame[1] < meanPostDrop + N_std*stDev):
    Laser_off_frame = frame[0]
    break

#print "Laser off:\t" + str(Laser_off_frame)

####################     Zero frame     ######################

zero_frame = -1
molasses_stage = 1
if (Laser_off_frame - 1) > dropFrame:
  zero_frame = Laser_off_frame - 1
if (Laser_off_frame - 1) == dropFrame:
  zero_frame = dropFrame
else:
  molasses_stage = 0
  if (frames[dropFrame-frames[0][0]] < (meanPostDrop + 6*stDev)):
    zero_frame = dropFrame - 1

if molasses_stage == 1:
  if (frames[zero_frame-frames[0][0]] < (meanPostDrop + 5*stDev)):
      zero_frame = dropFrame - 1

#print "Zero:\t" + str(zero_frame)

####################     Flash     ######################
# moving backwards find the peak highest above mean + std 
# iterate, lowering the threshold (N_std*stDev)

flash_frame = -1
while N_std > 0: # loop over incrementally smaller numbers of std.devs
  for frame in reversed(frames): # step backwards through frames
    if (frame[0] > Laser_off_frame and flash_frame == -1):
      if frame[1] > (meanPostDrop + N_std*stDev):
        flash_frame = frame[0]
  if flash_frame == -1:
    N_std -= 1
  else:
    break

if output == "1":
  print zero_frame
elif output == "2":
  print flash_frame
else:
  print "No output specified"
