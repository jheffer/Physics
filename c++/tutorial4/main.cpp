#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>	// for setw(), setprecision()
#include <algorithm>	// for sort()

#include "Particle.h"
#include "Electron.h"

using namespace std;

// Energy comparison function for Muons
bool cmpE (const Muon &m1, const Muon &m2) {
  return m1.getEnergy() < m2.getEnergy();
}

int main() {

  // define a vector of particles i.e. a vertex
  // it's a vector of pointers of type Particle
  //vector<Particle*> v1;

  // Create two Muons and compare their energies using member function operator()
/*  Muon muon1(1e10,0,0);
  Muon muon2(1e5,0,0);
  cout << "E(Muon 1) = " << muon1.getEnergy() << "\nE(Muon 2) = " << muon2.getEnergy() << endl;
  cout << muon1(muon2) << endl;*/

  // vector of Muons
  vector<Muon> mv1;

  // define iterator
  //vector<Particle*>::iterator i;
//  vector<Muon>::iterator i;

  // open Muon data file
  fstream myMuons("Muon.data", ios::in );

  // check the file is open
  if( myMuons.is_open() ) {
    // cursor at start of file
    myMuons.seekg(0);
    // push muons to vector
    while (!myMuons.eof()) {
      double x,y,z;
      myMuons >> x >> y >> z;
      mv1.push_back(Muon(x,y,z));
    }
  } else {
    cout << "File error." << endl;
  }

  // comparison function
/*  struct {
    bool operator()(const Muon &a, const Muon &b) {   
      if ( a.getEnergy() > b.getEnergy() ) { return true; }
      return false;
    }   
  } cmpE;*/

  // sort the vector by energy
  sort( mv1.begin() , mv1.end() , cmpE );

  // close Muons.data
  myMuons.close();

  // Print ordered Muon energies to screen
  for (int i = 0 ; i < mv1.size() ; i++) {
    cout << setprecision(20) << mv1[i].getEnergy() << endl;
  }

  /* Write data for Particle vector */
/*
  // open output text file
  // write-only, delete previous contents
  fstream myFile("myTable.txt", ios::out | ios::trunc );

  // check the file is open
  if( myFile.is_open() ) {
    // loop over iterator (i = pointer to a pointer)
    for (i = mv1.begin(); i != mv1.end(); ++i) {
      myFile
        << setw(10) << left << (*i)->getType()
        << setw(5) << right << (*i)->getId()
        << setw(10) << fixed << setprecision(3) << (*i)->getMass()
        << setw(5) << (*i)->getCharge()
      << endl;
    }
  } else {
    cout << "File error." << endl;
  }

  // close file
  myFile.close();
*/

  // clear Muon vector
  mv1.clear();  

  return 0;
}
