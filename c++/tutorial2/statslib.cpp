#include <iostream>
#include <cmath>
#include "statslib.h"

using namespace std;

// Introduction to Programming using C++
// Tutorial Two: Question 2
// Author: Carl Gwilliam <gwilliam@hep.ph.liv.ac.uk>

// calculate the mean value of the sample
float getMean(float* sample, int size) {

  // calculate sum of sample
  int sampleCount = 0;
  float sum = 0;
  while (++sampleCount <= size) sum += sample[sampleCount-1];
  
  // calculate and return mean
  return (sum / size);
}

// calculate the standard deviation of the sample
float getStdev(float* sample, int size) {

  // get mean of sample
  float mean = getMean(sample,size);

  // calculate x_i - mean
  float meanDev = 0;
  int sampleCount = 0;
  while (++sampleCount <= size)
    meanDev += pow((sample[sampleCount-1] - mean),2);

  // calculate standard deviation
  float stdev = sqrt( meanDev / size);

  return stdev;
}

// display the sample in order of lowest first
void getOrder(float* sample, int size) {
  
  // bubble sort algorithm 
  for (int i = 0; i < (size - 1); i++) {
    for (int j = 0; j < (size - 1); j++) {
      
      if (sample[j] > sample[j+1]) {
        float swap = sample[j];
        sample[j] = sample[j+1];
        sample[j+1] = swap;
      }
    }
  }

  cout << "correct order: ";
  for (int i = 0; i < size; i++) cout << sample[i] << " ";
  cout << endl;

  return;
}
