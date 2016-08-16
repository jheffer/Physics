#include <iostream>
#include "point.h"
#include "line.h"
#include "rectangle.h"

using namespace std;

int main() {

  // create rectangles to test
  rectangle r0;
  rectangle r1(3,6);
  rectangle r2(3,6,point(1,2,0));

  // test isWithin() function
  //point p1(0.5,0.5,0);
  //cout << r0.isWithin(p1) << endl;

  // test overlaps
  cout << "r0.isOverlap(r1) = " << r0.isOverlap(r1) << endl;
  cout << "r0.isOverlap(r2) = " << r0.isOverlap(r2) << endl;
  cout << "r1.isOverlap(r2) = " << r1.isOverlap(r2) << endl;

  return 0;
}
