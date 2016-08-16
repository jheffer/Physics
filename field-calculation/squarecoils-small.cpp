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

// Two square coils spaced by a large distance

int main()
{
  // Coil properties
  const double a(0.05); // square side size/m
  const double S = 0.2; // coil spacing/m
  const double I0 = 0.01; // current/A
  const int N = 20; // number of turns

  // Data range
  const int probe_points = 101; // how many data points
  const double probe_start = -0.05;
  const double probe_end = +0.05;
  const int integrating_factor = 1; // how many steps to divide vertexes into when calculating field

  // square coils
  vector<vect> coil1;
  vector<vect> coil2;

  coil1.push_back( vect(-S/2, +a/2, +a/2) );
  coil1.push_back( vect(-S/2, -a/2, +a/2) );
  coil1.push_back( vect(-S/2, +a/2, -a/2) );
  coil1.push_back( vect(-S/2, -a/2, -a/2) );
  
  coil2.push_back( vect(+S/2, +a/2, +a/2) );
  coil2.push_back( vect(+S/2, -a/2, +a/2) );
  coil2.push_back( vect(+S/2, +a/2, -a/2) );
  coil2.push_back( vect(+S/2, -a/2, -a/2) );

  //cout << "i\tx\ty\tz\n"; // print vertices
  //for (int i(0); i < coil1.size(); i++) cout << i << "\t" << coil1[i].getX() << "\t" << coil1[i].getY() << "\t" << coil1[i].getZ() << endl;

  // current flows (from shapes)
  vector<current> curr1;
  vector<current> curr2;

  for (int i(0); i < N; i++) // ten turns
  {
    for (int i(0); i < coil1.size(); i++) curr1.push_back(current(coil1[i], coil1[i+1], I0)); // add currents
    curr1.push_back(current(coil1[coil1.size()-1], coil1[0], I0)); // close the loop
    for (int i(0); i < coil2.size(); i++) curr2.push_back(current(coil2[i], coil2[i+1], I0));
    curr2.push_back(current(coil2[coil2.size()-1], coil2[0], I0));
  }

  //cout << "i\tx\ty\tz\tx\ty\tz\n"; // print current start and end points
  //for (int i(0); i < curr1.size(); i++) cout << i << "\t" << curr1[i].getStart().getX() << "\t" << curr1[i].getStart().getY() << "\t" << curr1[i].getStart().getZ() << "\t" << curr1[i].getEnd().getX() << "\t" << curr1[i].getEnd().getY() << "\t" << curr1[i].getEnd().getZ() << endl;

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
        for (int i(0); i < curr1.size(); i++) B.AddCurrent(curr1[i], integrating_factor); // calculate magnetic field, one current element at a time
        for (int i(0); i < curr2.size(); i++) B.AddCurrent(curr2[i], integrating_factor);

        // Print results
        cout << B.getPos().getX() << "\t" << B.getPos().getY() << "\t" << B.getPos().getZ()<< "\t"; // print position and
        cout << B.getVec().getX()<< "\t" << B.getVec().getY()<< "\t" << B.getVec().getZ() << endl; // magnetic field components
//      }
//    }
//  cout << "\n"; // blank line required for Gnuplot pm3d
  }
  return 0;
}
