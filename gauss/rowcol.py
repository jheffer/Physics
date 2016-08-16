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
xAxis = []
yAxis = []
for j,row in enumerate(data): # loop rows
  yAxis.append(0) # array integer for each row
  for i,intensity in enumerate(row): # loop columns
    yAxis[j] += int(intensity)
    if j == 0: # declare elements in xAxis
      xAxis.append(0)
    xAxis[i] += int(intensity)

# Write results to results text file
datax = open(sys.argv[1][:-4]+"-x.txt", "w")
datax.write("# x/px\tsum(intensity)\n")
for index,value in enumerate(xAxis):
    datax.write(str(index) + "\t" + str(value) + "\n")

datay = open(sys.argv[1][:-4]+"-y.txt", "w")
datay.write("# y/px\tsum(intensity)\n")
for index,value in enumerate(yAxis):
    datay.write(str(index) + "\t" + str(value) + "\n")
