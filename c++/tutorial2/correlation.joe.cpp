#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "statslib.h"
#include "statsfiles.h"

using namespace std;

// Joe Heffer
// Tutorial 2: Question 2 
// I used Pearson product-moment correlation coefficient
// http://en.wikipedia.org/wiki/Pearson_product-moment_correlation_coefficient

// function prototypes
//float getXYmean(float* sample_x, float* sample_y, int size);
float mean(float* sample, int size);
float sigma(float* sample, int size);
float covar(float* sample_x, float* sample_y, int size);

int main() {

  // sample of fixed size
  int size = 10;

  // get two data samples from file
  float* sample1 = getFileData("heightsample");
  float* sample2 = getFileData("weightsample");

/*    
  // get (xy)mean
  float xymean = getXYmean(sample1, sample2, size);
  cout << "xymean = " << xymean << endl;

  // get x mean * y mean
  mean1 = mean(sample1, size);
  mean2 = mean(sample2, size);
  float xmeanymean = mean1 * mean2;
  cout << "x_mean * y_mean = " << xmeanymean << endl;

  // get sig_x * sig_y
  float sig_1 = sigma(sample1, size);
  float sig_2 = sigma(sample2, size);
  cout << "sig_1 = " << sig_1 << endl;
  cout << "sig_2 = " << sig_2 << endl;
  float sigxy = sig_1 * sig_2;
  cout << "sig_1 * sig_2 = " << sigxy << endl;
*/
 
  // sigma
  float sig_1 = sigma(sample1, size);
  float sig_2 = sigma(sample2, size);

  // get cov(x,y)
  float cov12 = covar(sample1, sample2, size);

  // get correlation
  float r = cov12 / (sig_1 * sig_2);

  // display correlation
  cout << "r = " << r << endl;

  return 0;
}

/*
float getXYmean(float* sample_x, float* sample_y, int size) {
  float x(0);
  // iterate through the ordered samples adding each 
  // of the components together
  for(int i = 0; i < size; i++){
	x = x + sample_x[i] * sample_y[i];
  }
  // divide total by size of the sample 
  x = x / size;
  return x;
}
*/

float mean(float* sample, int size){
  float x(0);
  for(int i = 0; i < size; i++){
	x = x + sample[i];
  }
  x = x / size;
  return x;
}

float sigma(float* sample, int size){
  float mu = mean(sample, size);
  float x(0);
  for(int i = 0; i < size; i++){
	x = x + pow(sample[i]-mu,2);
  }
  x = sqrt(x/size);
  return x;
}

// covariance
float covar(float* sample_x, float* sample_y, int size) {
  float x(0);
  float meanx = mean(sample_x, size);
  float meany = mean(sample_y, size);
  for(int i = 0; i < size; i++){
	x = x + (sample_x[i] - meanx)*(sample_y[i] - meany);
  }
  x = x / size;
  return x;
}
