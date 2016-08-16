# -*- coding: utf-8 -*-
import re # regular expression for splitting via "\t" and " "
import sys
import math

# Find the region of interest around a peak

# Load data from text file
with open(str(sys.argv[1]).strip()) as f:
  content = f.readlines()

i=0
for line in content:
   i += 1
print i
