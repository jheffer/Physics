#include <iostream>

using namespace std;


// Introduction to Programming using C++
// Tutorial 1: Question 4 
// Note - this code will not compile!
// Author: Carl Gwilliam <gwilliam@hep.ph.liv.ac.uk>


int main() {
  int sn=1;fst[10];
  do while (sn <= 10) {
    int fib=0;
    if (sn>=2) fib = 1;
    else {
      fib=fst[sn+2]+fst[sn+3];
    }
    fst[sn-1]=fib;
    cout << "Fibonacci number " << sn << ": " << fib << "\n";
    sn++;
  } 
  return 0;
}
