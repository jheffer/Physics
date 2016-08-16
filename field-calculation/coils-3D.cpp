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

// 3 pairs of coils (symmetric set-up)
// with large coil separation relative to radius

int main()
{
  // Coil properties
  const int V = 24; // number of vertices
  const double R(0.05); // radius/m
  const int N = 20; // number of turns
  const double S = 0.20; // spacing/m
  const double Ix = 0.01; // x-axis current/A
  const double Iy = 0.01; // y-axis current/A
  const double Iz = 0.01; // z-axis current/A

  // Data range
  const int probe_points = 101;
  const double probe_start = -0.01;
  const double probe_end = +0.01;
  const int integrating_factor = 1; // how many steps to divide vertexes into when calculating field

  // Coil shapes constructed of V vertices
  vector<vect> coilX1; // x-axis
  vector<vect> coilX2;
  vector<vect> coilY1; // y-axis
  vector<vect> coilY2;
  vector<vect> coilZ1; // z-axis
  vector<vect> coilZ2;

  for (int i(0); i < V; i++) coilX1.push_back( vect(-S/2, R*cos(2*Pi*double(i)/V), R*sin(2*Pi*double(i)/V)) ); // x-axis
  for (int i(0); i < V; i++) coilX2.push_back( vect(+S/2, R*cos(2*Pi*double(i)/V), R*sin(2*Pi*double(i)/V)) );
  for (int i(0); i < V; i++) coilY1.push_back( vect(R*cos(2*Pi*double(i)/V), -S/2, R*sin(2*Pi*double(i)/V)) ); // y-axis
  for (int i(0); i < V; i++) coilY2.push_back( vect(R*cos(2*Pi*double(i)/V), +S/2, R*sin(2*Pi*double(i)/V)) );
  for (int i(0); i < V; i++) coilZ1.push_back( vect(R*cos(2*Pi*double(i)/V), R*sin(2*Pi*double(i)/V), -S/2) ); // z-axis
  for (int i(0); i < V; i++) coilZ2.push_back( vect(R*cos(2*Pi*double(i)/V), R*sin(2*Pi*double(i)/V), +S/2) );

  //cout << "i\tx\ty\tz\n"; // print circle points
  //for (int i(0); i < coilX1.size(); i++) cout << i << "\t" << coilX1[i].getX() << "\t" << coilX1[i].getY() << "\t" << coilX1[i].getZ() << endl;

  // current flows (from shapes)
  vector<current> currX1;
  vector<current> currX2;
  vector<current> currY1;
  vector<current> currY2;
  vector<current> currZ1;
  vector<current> currZ2;

  for (int i(0); i < N; i++) // N turns of the coil
  {
    for (int i(0); i < V; i++) currX1.push_back(current(coilX1[i], coilX1[i+1], Ix)); // x-axis
    currX1.push_back(current(coilX1[V-1], coilX1[0], Ix)); // close the loop
    for (int i(0); i < V; i++) currX2.push_back(current(coilX2[i], coilX2[i+1], Ix));
    currX2.push_back(current(coilX2[V-1], coilX2[0], Ix));
    for (int i(0); i < V; i++) currY1.push_back(current(coilY1[i], coilY1[i+1], Iy)); // y-axis
    currY1.push_back(current(coilY1[V-1], coilY1[0], Iy));
    for (int i(0); i < V; i++) currY2.push_back(current(coilY2[i], coilY2[i+1], Iy));
    currY2.push_back(current(coilY2[V-1], coilY2[0], Iy));
    for (int i(0); i < V; i++) currZ1.push_back(current(coilZ1[i], coilZ1[i+1], Iz)); // z-axis
    currZ1.push_back(current(coilZ1[V-1], coilZ1[0], Iz));
    for (int i(0); i < V; i++) currZ2.push_back(current(coilZ2[i], coilZ2[i+1], Iz));
    currZ2.push_back(current(coilZ2[V-1], coilZ2[0], Iz));
  }

  //cout << "i\tx\ty\tz\tx\ty\tz\n"; // print current start and end points
  //for (int i(0); i < currX1.size(); i++) cout << i << "\t" << currX1[i].getStart().getX() << "\t" << currX1[i].getStart().getY() << "\t" << currX1[i].getStart().getZ() << "\t" << currX1[i].getEnd().getX() << "\t" << currX1[i].getEnd().getY() << "\t" << currX1[i].getEnd().getZ() << endl;

  // Calculate magnetic field
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
        for (int i(0); i < currX1.size(); i++) B.AddCurrent(currX1[i], integrating_factor); // one current element at a time
        for (int i(0); i < currX2.size(); i++) B.AddCurrent(currX2[i], integrating_factor);
        for (int i(0); i < currY1.size(); i++) B.AddCurrent(currY1[i], integrating_factor);
        for (int i(0); i < currY2.size(); i++) B.AddCurrent(currY2[i], integrating_factor);
        for (int i(0); i < currZ1.size(); i++) B.AddCurrent(currZ1[i], integrating_factor);
        for (int i(0); i < currZ2.size(); i++) B.AddCurrent(currZ2[i], integrating_factor);

        // Print results
        cout << B.getPos().getX() << "\t" << B.getPos().getY() << "\t" << B.getPos().getZ()<< "\t"; // print position and
        cout << B.getVec().getX()<< "\t" << B.getVec().getY()<< "\t" << B.getVec().getZ() << endl; // magnetic field components
//      }
//    }
//  cout << "\n"; // blank line required for Gnuplot pm3d
  }

  return 0;
}
