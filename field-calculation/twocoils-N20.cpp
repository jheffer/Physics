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

// Two coils spaced by a large distance (displaced Helmholtz coil configuration.)

int main()
{
  // Coil properties
  const int circle_points = 24; // number of vertices
  const double R(0.05); // circle radius/m
  const double I0 = 0.01; // current/A
  const int N = 20; // number of turns

  // Data range
  const int probe_points = 101;
  const double probe_start = -0.2;
  const double probe_end = +0.2;
  const int integrating_factor = 1; // how many steps to divide vertexes into when calculating field

  // circle
  vector<vect> circleX1;
  vector<vect> circleX2;

  for (int i(0); i < circle_points; i++) circleX1.push_back(vect(-2*R, R*cos(2*Pi*double(i)/circle_points), R*sin(2*Pi*double(i)/circle_points)));
  for (int i(0); i < circle_points; i++) circleX2.push_back(vect(+2*R, R*cos(2*Pi*double(i)/circle_points), R*sin(2*Pi*double(i)/circle_points)));

  //cout << "i\tx\ty\tz\n"; // print circle points
  //for (int i(0); i < circleX1.size(); i++) cout << i << "\t" << circleX1[i].getX() << "\t" << circleX1[i].getY() << "\t" << circleX1[i].getZ() << endl;

  // current (from circles)
  vector<current> currX1;
  vector<current> currX2;

  for (int i(0); i < N; i++) // ten turns
  {
    for (int i(0); i < circle_points; i++) currX1.push_back(current(circleX1[i], circleX1[i+1], I0));
    currX1.push_back(current(circleX1[circle_points-1], circleX1[0], I0)); // close the loop
    for (int i(0); i < circle_points; i++) currX2.push_back(current(circleX2[i], circleX2[i+1], I0));
    currX2.push_back(current(circleX2[circle_points-1], circleX2[0], I0)); // close the loop
  }

  //cout << "i\tx\ty\tz\tx\ty\tz\n"; // print current start and end points
  //for (int i(0); i < currX1.size(); i++) cout << i << "\t" << currX1[i].getStart().getX() << "\t" << currX1[i].getStart().getY() << "\t" << currX1[i].getStart().getZ() << "\t" << currX1[i].getEnd().getX() << "\t" << currX1[i].getEnd().getY() << "\t" << currX1[i].getEnd().getZ() << endl;

  // Calculate magnetic field vectors around the centre of the wire, in plane perpendicular to it
  vect X; // current spatial position
  double probe_step ((probe_end-probe_start)/double(probe_points-1));
  cout << "#x\ty\tz\tB_x\tB_y\tB_z\n" << setprecision(3); // column headers

  for (int i(0); i < probe_points; i++) // scan x
  {
//    for (int j(0); j < probe_points; j++)
//    {
//      for( int k(0); k < probe_points; k++)
//      {
//        X.setVect(probe_start+i*probe_step, probe_start+j*probe_step, probe_start+k*probe_step); // calculate current position
        X.setVect(probe_start+i*probe_step, 0, 0); // y=0, z=0
        field B(X); // magnetic field value at each position X (initially zero)

        // Calculate magnetic field
        for (int i(0); i < currX1.size(); i++) B.AddCurrent(currX1[i], integrating_factor); // calculate magnetic field, one current element at a time
        for (int i(0); i < currX2.size(); i++) B.AddCurrent(currX2[i], integrating_factor);

        // Print results
        cout << B.getPos().getX() << "\t" << B.getPos().getY() << "\t" << B.getPos().getZ()<< "\t"; // print position and
        cout << B.getVec().getX()<< "\t" << B.getVec().getY()<< "\t" << B.getVec().getZ() << endl; // magnetic field components
//      }
//    }
//  cout << "\n"; // blank line required for Gnuplot pm3d
  }
  return 0;
}
