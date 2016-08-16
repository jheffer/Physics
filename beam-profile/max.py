#!/usr/bin/python

import sys
import os

# Read data to 2D array
file = open(sys.argv[1], "r")
data = []
for line in file:
  if(line.strip()[0] != "#"):
    data.append(int(line.strip().split("\t")[1]))

max = -1
for value in data:
  if(value > max):
    max = value

print max
