#ifndef VECTOR_H
#define VECTOR_H

class point;
const double PI = 3.14157;

class vect {
 public:
  vect();
  vect(double x, double y, double z);
  vect(point a, point b);
  vect(const vect&); // copy constructor -- pass by reference
  ~vect();  
  void setX(double x) {itsX = x;}
  void setY(double y) {itsY = y;}
  void setZ(double z) {itsZ = z;}
  double getX() const {return itsX;}
  double getY() const {return itsY;}
  double getZ() const {return itsZ;}
  double dotProduct(const vect& rhs) const;
  vect crossProduct(const vect& rhs) const;
  double getAngle(const vect& rhs) const;
  vect operator+ (const vect& rhs);
  vect operator- (const vect& rhs);
  vect operator* (const vect& rhs);
//  vect& operator= (const vect& rhs);
  void show() const;
 private:
  double getMagnitude() const;
  double itsX;
  double itsY;
  double itsZ;
};
#endif
