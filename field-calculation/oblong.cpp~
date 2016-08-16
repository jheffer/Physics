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

// What happens if the shape is asymmetric?

using namespace std;

int main()
{
  // coil properties
  const double a(0.83), b(0.6); // square side size/m
  const double S(0.83); // coil spacing/m
  const double I0(1); // physical current/A
  const int N(18*1); // number of turns
  const double I(I0*N); // effective current after N turns

  // output data properties
  const int probe_points = 100; // data resolution
  const double probe_start = -0.5; // data range
  const double probe_end = +0.5;
  const int Nint = 10; // number of vector divisions for field calculation

  // square coils
  vector<vect> coil0;
  vector<vect> coil1;

  coil0.push_back( vect(-S/2, +a/2, +b/2) ); // square, sides a, in y-z plane
  coil0.push_back( vect(-S/2, -a/2, +b/2) );
  coil0.push_back( vect(-S/2, -a/2, -b/2) );
  coil0.push_back( vect(-S/2, +a/2, -b/2) );
 
  coil1.push_back( vect(+S/2, +a/2, +b/2) );
  coil1.push_back( vect(+S/2, -a/2, +b/2) );
  coil1.push_back( vect(+S/2, -a/2, -b/2) );
  coil1.push_back( vect(+S/2, +a/2, -b/2) );

  //cout << "i\tx\ty\tz\n"; // print vertices
  //for (int i(0); i < coil.size(); i++) cout << i << "\t" << coil[i].getX() << "\t" << coil[i].getY() << "\t" << coil[i].getZ() << endl;

  // current flows (from shapes)
  vector<current> curr0;
  vector<current> curr1;

  for (int i(0); i < coil0.size() - 1; i++) curr0.push_back(current(coil0[i], coil0[i+1], I)); // add currents
  curr0.push_back(current(coil0[coil0.size()-1], coil0[0], I)); // close the loop
  for (int i(0); i < coil1.size() - 1; i++) curr1.push_back(current(coil1[i], coil1[i+1], I));
  curr1.push_back(current(coil1[coil1.size()-1], coil1[0], I));

  //cout << "\tStart\t\t\tEnd\ni\tx\ty\tz\tx\ty\tz\n"; // print current start and end points
  //for (int i(0); i < curr0.size(); i++) cout << i << "\t" << curr[i].getStart().getX() << "\t" << curr[i].getStart().getY() << "\t" << curr[i].getStart().getZ() << "\t" << curr[i].getEnd().getX() << "\t" << curr[i].getEnd().getY() << "\t" << curr[i].getEnd().getZ() << endl;

  // Calculate magnetic field vectors around the centre of the wire, in plane perpendicular to it
  vect X; // current spatial position
  double probe_step ((probe_end-probe_start)/double(probe_points-1));
  cout << "#x/m\ty/m\tz/m\tB_x/T\tB_y/T\tB_z/T\n" << setprecision(5); // column headers

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
        for (int i(0); i < curr0.size(); i++) B.AddCurrent(curr0[i], Nint); // calculate magnetic field, one current element at a time
        for (int i(0); i < curr1.size(); i++) B.AddCurrent(curr1[i], Nint);

        // Print results
        cout << B.getPos().getX() << "\t" << B.getPos().getY() << "\t" << B.getPos().getZ()<< "\t"; // print position and
        cout << B.getVec().getX()<< "\t" << B.getVec().getY()<< "\t" << B.getVec().getZ() << endl; // magnetic field components
//      }
//    }
//  cout << "\n"; // blank line required for Gnuplot pm3d
  }
  return 0;
}
