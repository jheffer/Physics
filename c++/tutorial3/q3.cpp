#include <iostream>
#include "point.h"
#include "vect.h"

using namespace std;

// Joe Heffer, Tutorial 3, Q3

int main() {

// part a
  vect a(-3,2,4);
  vect b(point(2,1,3),point(6,3,5));
  vect c(a);
  vect d=b;

// part b
  cout << "a.b = " << a.dotProduct(b) << endl;
  cout << "a*b = ";
  vect aCrossb(a.crossProduct(b));
  cout << "a+b = ";
  vect aPlusb(a+b);
  cout << "a-b = ";
  vect aSubb(a-b);

// part c
  cout << "c.d = " << c.dotProduct(d) << endl;
  cout << "c*d = ";
  vect cCrossd(c.crossProduct(d));
  return 0;
}
