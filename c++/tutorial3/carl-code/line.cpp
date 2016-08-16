#include <iostream>
#include <cmath>
#include "line.h"

using namespace std;

// Source code from Introduction to Programming using C++
// Solutions
// Tutorial 2: Question 4
// line member function implementation file
// Author: Carl Gwilliam <gwilliam@hep.ph.liv.ac.uk>

// constructor with origin and direction
Line::Line(Point o, float x, float y, float z) {
  the_startPoint = o;
  itsXdir = x;
  itsYdir = y;
  itsZdir = z;
}

// constructor with direction of line
Line::Line(float x, float y, float z) {
  Point o;
  the_startPoint = o;
  itsXdir = x;
  itsYdir = y;
  itsZdir = z;
}

// constructor to make line between two points
Line::Line(Point a, Point b) {
  the_startPoint = a;
  itsXdir = b.getX() - a.getX();
  itsYdir = b.getY() - a.getY();
  itsZdir = b.getZ() - a.getZ();
}

// destructor
Line::~Line() {
}

// get x direction of line
float Line::getXdir() {
  return itsXdir;
}

// get y direction of line
float Line::getYdir() {
  return itsYdir;
}

// get z direction of line
float Line::getZdir() {
  return itsZdir;
}

// get starting point
Point Line::getStartPoint() {
  return the_startPoint;
}


// calculate distance between the line and a given point 
float Line::distance(Point p) {
  // your code here
}
