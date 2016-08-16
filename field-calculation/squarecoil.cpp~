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

// One square coil
// Should look like this, Eq. 9:
// http://www.physicspages.com/2013/04/11/magnetic-field-of-square-current-loop/
// aim for 3 G

int main()
{
  // coil properties
  const double a(0.05); // square side size/m
  const double I0 = 0.01; // physical current/A
  const int N = 10; // number of turns
  const double I = I0*N; // effective current after N turns

  // data range
  const int probe_points = 100;
  const double probe_start = -0.2;
  const double probe_end = +0.2;
  const int Nint = 10; // number of vector divisions for field calculation

  // square coils
  vector<vect> coil;

  coil.push_back( vect(0, +a/2, +a/2) ); // square, sides a, in y-z plane
  coil.push_back( vect(0, -a/2, +a/2) );
  coil.push_back( vect(0, -a/2, -a/2) );
  coil.push_back( vect(0, +a/2, -a/2) );
 
  //cout << "i\tx\ty\tz\n"; // print vertices
  //for (int i(0); i < coil.size(); i++) cout << i << "\t" << coil[i].getX() << "\t" << coil[i].getY() << "\t" << coil[i].getZ() << endl;

  // current flows (from shapes)
  vector<current> curr;

  for (int i(0); i < coil.size() - 1; i++) curr.push_back(current(coil[i], coil[i+1], I)); // add currents
  curr.push_back(current(coil[coil.size()-1], coil[0], I)); // close the loop

  //cout << "\tStart\t\t\tEnd\ni\tx\ty\tz\tx\ty\tz\n"; // print current start and end points
  //for (int i(0); i < curr.size(); i++) cout << i << "\t" << curr[i].getStart().getX() << "\t" << curr[i].getStart().getY() << "\t" << curr[i].getStart().getZ() << "\t" << curr[i].getEnd().getX() << "\t" << curr[i].getEnd().getY() << "\t" << curr[i].getEnd().getZ() << endl;

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
        for (int i(0); i < curr.size(); i++) B.AddCurrent(curr[i], Nint); // calculate magnetic field, one current element at a time

        // Print results
        cout << B.getPos().getX() << "\t" << B.getPos().getY() << "\t" << B.getPos().getZ()<< "\t"; // print position and
        cout << B.getVec().getX()<< "\t" << B.getVec().getY()<< "\t" << B.getVec().getZ() << endl; // magnetic field components
//      }
//    }
//  cout << "\n"; // blank line required for Gnuplot pm3d
  }
  return 0;
}
