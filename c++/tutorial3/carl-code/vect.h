#ifndef VECTOR_H
#define VECTOR_H

// Source code from Introduction to Programming using C++
// Tutorial 3: Question 1
// vector interface
// Author: Carl Gwilliam <gwilliam@hep.ph.liv.ac.uk>

class Point;
const double PI = 3.14157;

class Vect {
 public:
  Vect();
  Vect(double x, double y, double z);
  Vect(Point a, Point b);
  Vect(const Vect&);
  ~Vect();  
  void setX(double x) {itsX = x;}
  void setY(double y) {itsY = y;}
  void setZ(double z) {itsZ = z;}
  double getX() const {return itsX;}
  double getY() const {return itsY;}
  double getZ() const {return itsZ;}
  double dotProduct(const Vect& rhs) const;
  Vect crossProduct(const Vect& rhs) const;
  double getAngle(const Vect& rhs) const;
  Vect operator+ (const Vect& rhs);
  Vect operator- (const Vect& rhs);
  Vect operator* (const Vect& rhs);
  Vect& operator= (const Vect& rhs);
 private:
  double getMagnitude() const;
  double itsX;
  double itsY;
  double itsZ;
};
#endif
