#include <iostream>
#include <cmath>
#include "line.h"

using namespace std;

// constructor with origin and direction
line::line(point o, float x, float y, float z) {
  the_startpoint = o;
  itsXdir = x;
  itsYdir = y;
  itsZdir = z;
}

// constructor with direction of line
line::line(float x, float y, float z) {
  point o;
  the_startpoint = o;
  itsXdir = x;
  itsYdir = y;
  itsZdir = z;
}

// constructor to make line between two points
line::line(point a, point b) {
  the_startpoint = a;
  itsXdir = b.getX() - a.getX();
  itsYdir = b.getY() - a.getY();
  itsZdir = b.getZ() - a.getZ();
}

// destructor
line::~line() {
}

// get x direction of line
float line::getXdir() {
  return itsXdir;
}

// get y direction of line
float line::getYdir() {
  return itsYdir;
}

// get z direction of line
float line::getZdir() {
  return itsZdir;
}

// get starting point
point line::getStartpoint() {
  return the_startpoint;
}

// the line's length (modulus)
float line::mod() const {
  return sqrt(pow(itsXdir,2) + pow(itsYdir,2) + pow(itsZdir,2));
}

// calculate the cross product of two vectors
line line::cross(line l) {
  float i = (itsYdir*l.getZdir() - itsZdir*l.getYdir());
  float j = (itsZdir*l.getXdir() - itsXdir*l.getZdir());
  float k = (itsXdir*l.getYdir() - itsYdir*l.getXdir());
  return line(i,j,k);
}

// calculate distance between the line and a given point 
float line::distance(point p) {
  line x(the_startpoint.getX()-p.getX(), the_startpoint.getY()-p.getY(), the_startpoint.getZ()-p.getZ());
  return (x.cross(*this)).mod()/this->mod();
}
