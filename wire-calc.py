#!/usr/bin/env python
"""
DESCRIPTION

  Calculate the electrical properties of the new coils.

AUTHOR

  Joe Heffer <jheffer@liv.ac.uk>
"""

import sys, os, traceback, optparse
import time
import re
import math
#from pexpect import run, spawn

def main ():

  # Constants
  global options, args
  pi = math.pi
  ro = 1.72e-8 # copper resistivity @ 20 C, ohm*m (1.68 for copper, 1.72 for annealed)
  u0 = 4*pi*1e-7 # permability free space/(Tm/A)
  m = 8960 # Cu density/(kg/m^3)
  c = 0.385e3 # copper specific heat capacity/(J/kgK)
  k = 385.0 # Cu thermal conductivity/(W/m*K)

  # Variables
  AWG = 16.3 # american wire gauge
  a = 1e-3 # flat wire thickness/m
  b = 15e-3 # flat wire width/m
  ways = 1 # ribbon cable number of ways
  coils = 1 # number of coils
  sides = 4 # number of sides of a square
  l = 0.80 # coil size/m
  S = 0.89 # distance between coils/m
  turns = 100 # number of turns of ribbon cable
  I = 0.1 # current/A

  # Calculations
  d = 0.127e-3 * pow(92,(36-float(AWG))/39) # wire diameter/m
  A = pi*(d/2)**2 # cross-sectional area (round)/m^2
  #A = a*b # cross-sectional area (rectangular)/m^2
  L = coils*sides*l*ways*turns # total length of copper wire/m
  Vol = A*L # volume/m^3
  R = ro*L/A # resistance/ohm
  V = I*R # Pot. diff./V
  P = I*V # Power/W
  M = Vol*m # mass of copper/kg
  H = P/(M*c)# heating rate/(K/s)
  h = k*(L*d)*H/d # Heat transfer J/s
	# http://hyperphysics.phy-astr.gsu.edu/hbase/thermo/heatra.html
  #h = k*L*(2*pi*(d/4))*H/(d/2) # heat conduction rate J/s
  
  # Magnetic field at MOT position [Griffiths2012]
  # http://www.physicspages.com/2013/04/11/magnetic-field-of-square-current-loop/
  B = coils * (4*l**2*u0*I*turns*ways) / (pi*math.sqrt(2*l**2 + 4*(S/2)**2)*(l**2 + 4*(S/2)**2))

  # Print to screen
  print "Copper wire intrinsic properties:"
  print
  print "AWG\t" + str(AWG)
  print "Dia.\t" + str(round(d*1e3,4)) + "\tmm"
  #print "Thcknss\t" + str(a*1e3) + "\tmm"
  #print "Width\t" + str(b*1e3) + "\tmm"
  print "Area\t" + str(round(A*1e6,4)) + "\tmm^2"
  print "Res.dns\t" + str(round(R/L,4)) + "\tOhm/m"
  print
  print "Single square coil properties:"
  print
  print "Size\t" + str(l) + "\tm"
  print "Turns\t" + str(turns)
  #print "Ways\t" + str(ways)
  #print "Length\t" + str(L/ways) + "\tm of ribbon cable"
  print "Length\t" + str(L) + "\tm of wire per coil (" + str(3*L) + " m for 3 coils)"
  print
  print "Electronic properties:"
  print
  print "I\t" + str(I) + "\tA"
  print "R\t" + str(round(R,4)) + "\tOhm"
  print "P.d.\t" + str(round(V,4)) + "\tV"
  print "P\t" + str(round(P,2)) + "\tW"
  print
  print "Magnetic field properties:"
  print
  print "B\t" + str(round(B*1e4,4)) + "\tG at " + str(round(S/2,2)) + " m from coil"
  print
  print "Thermal properties:"
  print
  print "Mass\t" + str(round(M,3)) + "\tkg"
  print "dT/dt\t" + str(round(H,4)) + "\tK/s\tJoule heating"
  print "dQ/dt\t" + str(round(h,1)) + "\tJ/s\tHeat transfer"

if __name__ == '__main__':
  try:
    start_time = time.time()
    parser = optparse.OptionParser(formatter=optparse.TitledHelpFormatter(), usage=globals()['__doc__'], version='$Id$')
    parser.add_option ('-v', '--verbose', action='store_true', default=False, help='verbose output')
    (options, args) = parser.parse_args()
    #if len(args) < 1:
    #  parser.error ('missing argument')
    if options.verbose: print time.asctime()
    main()
    if options.verbose: print time.asctime()
    if options.verbose: print 'TOTAL TIME IN MINUTES:',
    if options.verbose: print (time.time() - start_time) / 60.0
    sys.exit(0)
  except KeyboardInterrupt, e: # Ctrl-C
    raise e
  except SystemExit, e: # sys.exit()
    raise e
  except Exception, e:
    print 'ERROR, UNEXPECTED EXCEPTION'
    print str(e)
    traceback.print_exc()
    os._exit(1)
