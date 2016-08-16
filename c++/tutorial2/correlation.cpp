#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "statslib.h"
#include "statsfiles.h"

using namespace std;

// Introduction to Programming using C++
// Tutorial
// Tutorial 2: Question 2 
// Note - compile: g++ correlation.cpp statslib.cpp statsfiles.cpp
// Author: Carl Gwilliam <gwilliam@hep.ph.liv.ac.uk>

// function prototypes
float getXYmean(float* sample_x, float* sample_y, int size);

int main() {

  // sample of fixed size
  int size = 10;

  // get two data samples from file
  float* sample1 = getFileData("heightsample");
  float* sample2 = getFileData("weightsample");
    
  // get (xy)mean

  // get x mean * y mean

  // get sig_x * sig_y

  // get correlation

  // display correlation

  return 0;
}

float getXYmean(float* sample_x, float* sample_y, int size) {

  // iterate through the ordered samples adding each 
  // of the components together

  // divide total by size of the sample 

  return mean;
}
