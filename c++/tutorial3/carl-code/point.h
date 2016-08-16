#ifndef POINT_H
#define POINT_H

// Source code from Introduction to Programming using C++
// Solutions
// Tutorial 2: Question 4
// point declaration file
// Author: Carl Gwilliam <gwilliam@hep.ph.liv.ac.uk>

class Line;

// declare point class
class Point {
public:
  Point(float x, float y, float z);
  Point();
  ~Point();
  void setX(float x);
  void setY(float y);
  void setZ(float z);
  float getX();
  float getY();
  float getZ();
  float distance();
  float distance(Point anotherPoint);
  float distance(Line);
private:
  float itsX;
  float itsY;
  float itsZ;
};
#endif
