#!/usr/bin/python

import sys
import os

# Read data to 2D array
file = open(sys.argv[1], "r")

data = []
for line in file:
  data.append(line.strip().split(" "))


#for j in data:
#  for i in j:
#   print(i+" "),
#  print

# Project data onto x and y axes
log = open("log.txt", "w")
xAxis = []
yAxis = []
xAxis_temp = []
yAxis_temp = []
count = 0
AOI = 60
MOT_y = 1
MOT_x = 2
count_y = 0
count_x = 0

mot_file = open("Images/mot_infomation.txt")
x = mot_file.readline() 
y = mot_file.readline()

MOT_x = float(x) 
MOT_y = float(y)

print MOT_x
print MOT_y

 
for j,row in enumerate(data): # loop rows
  #yAxis.append(0) # array integer for each row
  count = 0
  for i,intensity in enumerate(row): # loop columns
    if i > (MOT_x-AOI/2) and i < (MOT_x+AOI/2):
      yAxis.append(0) # array integer for each row
      yAxis[j] += int(intensity)
      count_y = count_y+1
    if j > (MOT_y-AOI/2) and j < (MOT_y+AOI/2):  # declare elements in xAxis
      if j == (MOT_y-AOI/2+1):
        if (i%2) == 0:
          xAxis.append(0)
      if (i%2)==0:
        if i>0:
          count = count+1
      log.write(str(i) + "\t" + str(count) + "\n")
      xAxis[count] += int(intensity)

#count = 0
#for i,intensity in xAxis_temp: #loop over xAxis_temp
#  if (i%2)==0:
#    xAxis[count]+=intensity
#  else:
#    xAxis[count]+=intensity
#    xAxis.append(0)1
#    count+=1

#count = 0
#for i in xAxis_temp: #loop over xAxis_temp
#  xAxis[i]= xAxis_temp[i] + xAxis_temp[i+1]

# Write results to results text file
datax = open(sys.argv[1][:-4]+"-x.txt", "w")
datax.write("# x/px\tsum(intensity)\n")
for index,value in enumerate(xAxis):
    datax.write(str(index) + "\t" + str(value) + "\n")

datay = open(sys.argv[1][:-4]+"-y.txt", "w")
datay.write("# y/px\tsum(intensity)\n")
for index,value in enumerate(yAxis):
    datay.write(str(index) + "\t" + str(value) + "\n")
