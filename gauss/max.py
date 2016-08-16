#!/usr/bin/python

import sys
import os

#
#    Print maximum value in a data file
#

# Read data to 2D array
file = open(str(sys.argv[1]).strip(), "r")
frames = []
for line in file:
  if(line.strip()[0] != "#"):
    frames.append( line.strip().split("\t")[1] ) # read only frame values

max = -1
for value in frames:
  if(value > max):
    max = value

print max
