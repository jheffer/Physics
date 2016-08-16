#include <iostream>
#include <iomanip>
#include "sample.h"

using namespace std;

// Joe Heffer, Tutorial 3, Q4

int main() {

  // Part a -- ordering

  char file1[] = "P1.cand";
  Sample P1(file1);
  Sample P1o(P1.order(),P1.getSize());

  // Part b -- correlation

  char file2[] = "P2.cand";
  Sample P2(file2);
  cout << "r(P1,P2) = " << P1.correlation(P2) << endl;

  // Part c -- r-matrix

  char file3[] = "openang.cand";
  Sample openang(file3);

  char file4[] = "phi1.cand";
  Sample phi1(file4);

  char file5[] = "phi2.cand";
  Sample phi2(file5);

  char file6[] = "thet1.cand";
  Sample thet1(file6);

  char file7[] = "thet2.cand";
  Sample thet2(file7);

  char file8[] = "thmiss.cand";
  Sample thmiss(file8);

  const int nVars = 8;
  Sample kinematics [nVars] = {P1, P2, openang, phi1, phi2, thet1, thet2, thmiss};
  for(int i=0;i<nVars;i++){
    for(int j=0;j<nVars;j++){
      cout << std::setprecision(1) << kinematics[i].correlation(kinematics[j]) << "\t";
    }
    cout << endl;
  }

  return 0;
}
