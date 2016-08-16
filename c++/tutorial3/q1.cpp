#include <iostream>
#include "point.h"
#include "line.h"

using namespace std;

int main() {

  // create our line between (2,1,8) and (3,-1,5)
  point p1(2,1,8);
  point p2(3,-1,5);
  line l1(p1, p2);

  cout << "l1 start = [" << l1.getStartpoint().getX()
	<< ", " << l1.getStartpoint().getY()
	<< ", " << l1.getStartpoint().getZ() << "]" << endl;
  cout << "l1 vector = [" << l1.getXdir()
	<< ", " << l1.getYdir()
	<< ", " << l1.getZdir() << "]" << endl;
  cout << "l1 length = " << l1.mod() << endl;

  // and another point (2,3,2)
  point p3(2,3,2);
  cout << "p3 = [" << p3.getX() << ", " << p3.getY() << ", " << p3.getZ() << "]" << endl;
  
  // distance
  cout << "l1.distance(p3) = " << l1.distance(p3) << endl;
  cout << "p3.distance(l1) = " << p3.distance(l1) << endl;

  return 0;
}
