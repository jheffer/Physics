#include <iostream>
#include <iomanip>
#include <cstdlib>
//#include <time.h>
#include <cmath>
//#include <fstream>
#include <vector>
#include"constants.h"
#include"vect.h"
#include"current.h"
#include"field.h"

using namespace std;

int main()
{
  const int circle_points = 24; // vertices
  const double circle_radius(0.5); // m
  const double I0 = 1.0; // current/A

  const int probe_points = 21;
  const double probe_start = -1.0;
  const double probe_end = +1.0;
  const int integrating_factor = 1; // how many steps to divide vertexes into when calculating field

  // circle
  vector<vect> circleX1;
  for (int i(0); i < circle_points; i++) circleX1.push_back(vect(0.0, circle_radius*cos(2*Pi*double(i)/circle_points), circle_radius*sin(2*Pi*double(i)/circle_points)));

  //cout << "i\tx\ty\tz\n"; // print circle points
  //for (int i(0); i < circleX1.size(); i++) cout << i << "\t" << circleX1[i].getX() << "\t" << circleX1[i].getY() << "\t" << circleX1[i].getZ() << endl;

  // current (from circles)
  vector<current> currX1;
  for (int i(0); i < circle_points; i++) currX1.push_back(current(circleX1[i], circleX1[i+1], I0));
  currX1.push_back(current(circleX1[circle_points-1], circleX1[0], I0));

  //cout << "i\tx\ty\tz\tx\ty\tz\n"; // print current start and end points
  //for (int i(0); i < currX1.size(); i++) cout << i << "\t" << currX1[i].getStart().getX() << "\t" << currX1[i].getStart().getY() << "\t" << currX1[i].getStart().getZ() << "\t" << currX1[i].getEnd().getX() << "\t" << currX1[i].getEnd().getY() << "\t" << currX1[i].getEnd().getZ() << endl;

  // Calculate magnetic field vectors around the centre of the wire, in plane perpendicular to it
  vect X; // current spatial position
  double probe_step ((probe_end-probe_start)/double(probe_points-1));
  cout << "#x\ty\tz\tB_x\tB_y\tB_z\n" << setprecision(3); // column headers

  for (int i(0); i < probe_points; i++)
  {
    for (int j(0); j < probe_points; j++)
    {
      for( int k(0); k < probe_points; k++)
      {
        X.setVect(probe_start+i*probe_step, probe_start+j*probe_step, probe_start+k*probe_step); // calculate current position
        field B(X); // magnetic field value at each position X (initially zero)
        for (int i(0); i < circle_points; i++) B.AddCurrent(currX1[i], integrating_factor); // calculate magnetic field, one current element at a time
        cout << B.getPos().getX() << "\t" << B.getPos().getY() << "\t" << B.getPos().getZ()<< "\t"; // print position and
        cout << B.getVec().getX()<< "\t" << B.getVec().getY()<< "\t" << B.getVec().getZ() << endl; // magnetic field components
      }
    }
  cout << "\n"; // blank line required for Gnuplot pm3d
  }
  return 0;
}
