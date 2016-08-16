#ifndef LINE_H
#define LINE_H

#include "point.h"

class line {
 public:  
  line(point o, float x, float y, float z); 
  line(float x, float y, float z);
  line(point a, point b);
  ~line();
  float getXdir();
  float getYdir();
  float getZdir();
  point getStartpoint();
  float distance(point p);
  float mod() const;
  line cross(line l);
 private:
  point the_startpoint;
  float itsXdir;
  float itsYdir;
  float itsZdir;
};
#endif
