#ifndef RECTANGLE_H
#define RECTANGLE_H

// Source code from Introduction to Programming using C++
// Tutorial 2: Question 5
// rectangle declaration file
// Author: Carl Gwilliam <gwilliam@hep.ph.liv.ac.uk>

#include "point.h"

class Rectangle {
 public:
  Rectangle();
  Rectangle(Point lowerLeft, Point upperRight); 
  Rectangle(float base, float height);
  Rectangle(float base, float height, Point offset);
  ~Rectangle();
  float getWidth();
  float getHeight();
  float getArea();
  bool isOverlap(Rectangle a);
 private:
  Point itsLowerLeft;
  Point itsLowerRight;
  Point itsUpperLeft;
  Point itsUpperRight;
};
#endif
