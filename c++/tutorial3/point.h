#ifndef POINT_H
#define POINT_H

class line;

// declare point class
class point {
public:
  point(float x, float y, float z);
  point();
  ~point();
  void setX(float x);
  void setY(float y);
  void setZ(float z);
  float getX();
  float getY();
  float getZ();
  float distance();
  float distance(point anotherpoint);
  float distance(line);
  void show() const;
private:
  float itsX;
  float itsY;
  float itsZ;
};
#endif
