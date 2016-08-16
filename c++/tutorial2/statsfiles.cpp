#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "statsfiles.h"

using namespace std;

// Introduction to Programming using C++
// Tutorial Two: Question 2
// Implementation file for functions reading data samples from file
// Author: Carl Gwilliam <gwilliam@hep.ph.liv.ac.uk>

// get data sample from filehandle
float* getFileData(const char* filename) {
//float* getFileData(char* filename) {

  ifstream sampleFile(filename);

  // set size maximum to 100
  float* sample = new float[100];

  // read sample values
  int size = 0;
  while( (!sampleFile.eof()) || (size < 100) ) {
    sampleFile >> sample[size++];
  } 
  size--;

  // close file
  sampleFile.close();

  return sample;
}
