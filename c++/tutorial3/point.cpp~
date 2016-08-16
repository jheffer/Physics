#include <iostream>
#include <cmath>
#include "point.h"
#include "line.h"

using namespace std;

// constructor
point::point(float x, float y, float z) {
  itsX = x;
  itsY = y;
  itsZ = z;
}

// constructor
point::point() {
  itsX = 0;
  itsY = 0;
  itsZ = 0;
}

// destructor
point::~point() {
}

// set x coordinate
void point::setX(float x) {
  itsX = x;
  return;
}

// set y coordinate
void point::setY(float y) {
  itsY = y;
  return;
}

// set z coordinate
void point::setZ(float z) {
  itsZ = z;
  return;
}

// get x coordinate
float point::getX() {
  return itsX;
}

// get y coordinate
float point::getY() {
  return itsY;
}

// get z coordinate
float point::getZ() {
  return itsZ;
}

// calculate distance from origin
float point::distance() {
  float distance = sqrt( pow(itsX,2) + pow(itsY,2) + pow(itsZ,2) );
  return distance;
}

// calculate distance from another point
float point::distance(point anotherpoint) {
  float difX = itsX - anotherpoint.itsX;
  float difY = itsY - anotherpoint.itsY;
  float difZ = itsZ - anotherpoint.itsZ;
  float distance = sqrt( pow(difX,2) + pow(difY,2) + pow(difZ,2) );
  return distance;
}

// calculate distance from a line
float point::distance(line l) {
  line x(l.getStartpoint().getX()-itsX, l.getStartpoint().getY()-itsY, l.getStartpoint().getZ()-itsZ);
  return (x.cross(l)).mod()/l.mod();
}
