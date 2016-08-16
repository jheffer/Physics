#ifndef LINE_H
#define LINE_H

#include "point.h"

// Source code from Introduction to Programming using C++
// Solutions
// Tutorial 2: Question 4
// declaration of line class
// Author: Carl Gwilliam <gwilliam@hep.ph.liv.ac.uk>

class Line {
 public:  
  Line(Point o, float x, float y, float z); 
  Line(float x, float y, float z);
  Line(Point a, Point b);
  ~Line();
  float getXdir();
  float getYdir();
  float getZdir();
  Point getStartPoint();
  float distance(Point p);
 private:
  Point the_startPoint;
  float itsXdir;
  float itsYdir;
  float itsZdir;
};
#endif
