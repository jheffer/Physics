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
    frames[i][1] = float(frame[1]) # normalised brightness
    frames[i][2] = int(frame[2])

####################     Drop frame     ######################

compare_drop = 0
for i,frame in enumerate(frames):
  if frame[0] != frames[-1][0]: # if not last frame  
    next = frames[i+1]
    if(frame[1] - next[1] > compare_drop):
      compare_drop = frame[1] - next[1]
      Drop_frame = frame[0]

#print "Drop:\t" + str(Drop_frame)

####################     Mean +/- sigma     ######################

# mean post-drop
sumPostDrop = 0.0
NpostDrop = 0
for frame in frames:
  if frame[0] > Drop_frame + clearance:
    sumPostDrop += frame[1]
    NpostDrop += 1 # count number of frames
meanPostDrop = sumPostDrop / NpostDrop

# variance
varSumPostDrop = 0.0
for frame in frames:
  if frame[0] > Drop_frame + clearance:
    varSumPostDrop += (frame[1] - meanPostDrop)*(frame[1] - meanPostDrop)
varPostDrop = varSumPostDrop / NpostDrop
standard_deviation = math.sqrt(varPostDrop)

#print "Post-drop mean:\t" + str(meanPostDrop) + " +/- " + str(standard_deviation)

# mean pre-drop
sumPreDrop = 0.0
NpreDrop = 0
for frame in frames:
  if frame[0] > Drop_frame:
    sumPreDrop += frame[1]
    NpreDrop += 1 # count number of frames
meanPreDrop = sumPreDrop / NpreDrop


####################     Lasers off     ######################

for frame in frames:
  if (frame[1] < meanPostDrop + N_std*standard_deviation):
    Laser_off_frame = frame[0]
    break

#print "Laser off:\t" + str(Laser_off_frame)

####################     Zero frame     ######################

molasses_stage = 1
if (Laser_off_frame - 1) > Drop_frame:
  zero_frame = Laser_off_frame - 1
if (Laser_off_frame - 1) == Drop_frame:
  zero_frame = Drop_frame
else:
  molasses_stage = 0
  if (frames[Drop_frame-frames[0][0]] < (meanPostDrop + 6*standard_deviation)):
    zero_frame = Drop_frame - 1

if molasses_stage == 1:
  if (frames[zero_frame-frames[0][0]] < (meanPostDrop + 5*standard_deviation)):
      zero_frame = Drop_frame - 1

#print "Zero:\t" + str(zero_frame)

####################     Flash     ######################
# moving backwards find the peak highest above mean + std 
# iterate, lowering the threshold (N_std*standard_deviation)

flash_frame = -1
while N_std > 0: # loop over incrementally smaller numbers of std.devs
  for frame in reversed(frames): # step backwards through frames
    if (frame[0] > Laser_off_frame and flash_frame == -1):
      if frame[1] > (meanPostDrop + N_std*standard_deviation):
        flash_frame = frame[0]
  if flash_frame == -1:
    N_std -= 1
  else:
    break

if output == "1":
  print flash_frame
elif output == "2":
  print zero_frame
elif output == "3":
  print meanPreDrop
else:
  print "No output specified"
