#include <iostream>
#include "cloud.h"
#include "CImg.h"

using namespace std;
using namespace cimg_library;

// Constructor (load bitmap file)
Cloud::Cloud(char * bmpFile)
{
  // Load and characterise data
  CImg<float> bmp(bmpFile); // load bitmap
  img = bmp; // save to this object
  width = img.width(); // image size
  height = img.height();
  this->calcPeak(); // brightest pixel
  this->calcROI(); // Find ROI near peak value

  // Set region of interest (ROI)
  int ROIwidth = xmax - xmin;
  int ROIheight = ymax - ymin;
  xAxis.resize(ROIwidth, 0); // initialise to zero
  yAxis.resize(ROIheight, 0);

  // Project data onto axes within ROI
  for (int i(0); i < ROIwidth; i++)// sum columns -> xAxis
  {
    for(int j(0); j < ROIheight; j++) xAxis[i] += img(xmin+i,ymin+j);
  }
  for(int j(0); j < ROIheight; j++) // rows -> yAxis
  {
    for (int i(0); i < ROIwidth; i++) yAxis[j] += img(xmin+i,ymin+j);
  }

  this->subBg(); // subtract background

  //cout << "i\tx\txAxis[i]" << endl;
  //for(int i(0); i<ROIwidth; i++) cout << i<<"\t" << i+xmin << "\t" << xAxis[i] << endl;

  //cout << "j\tx\tyAxis[j]" << endl;
  //for(int i(0); i<ROIheight; i++) cout << i<<"\t" << i+ymin << "\t" << yAxis[i] << endl;

  // Calculate statistical properties
  meanX = xmin + mean(&xAxis); // mean() returns position inside ROI
  meanY = ymin + mean(&yAxis);
  varX = var(&xAxis, meanX-xmin);
  varY = var(&yAxis, meanY-ymin);
}

void Cloud::subBg()
{
  // subtract background = average pixel at edge of ROI
  int bgX = (xAxis.at(0)+xAxis.at(xmax-xmin-1))/2;
  for (int i(0); i < xAxis.size(); i++) xAxis.at(i) -= bgX;

  int bgY = (yAxis.at(0)+yAxis.at(ymax-ymin-1))/2;
  for (int j(0); j < yAxis.size(); j++) yAxis.at(j) -= bgY;
}

void Cloud::calcPeak()
{
  // highest pixel value
  // Loop over rows and columns, find brightest
  int maxVal(0);
  for (int i(0); i < width; i++)
  {
    for(int j(0); j < height; j++)
    {
      if(img(i,j) >= maxVal) // if brightest point
      {
        maxVal = img(i,j);
        peakX = i; // set peak position
        peakY = j;
      }
    }
  }
}

// Set ROI to be double the e^-2 radius
void Cloud::calcROI()
{
  double threshold = 0.13533528323; // e^-2

  // step right (+x) from peak until value drops below threshold
  for(int i(peakX); i < width; i++){
    if(img(i,peakY) < img(peakX,peakY)*threshold) {xmax = i+(i-peakX); break;}
  }
  if(xmax == 0) xmax = width-1; // default to full image size
  if(xmax > width-1) xmax = width-1;

  // -x
  for(int i(peakX); i >= 0; i--){
    if(img(i,peakY) < img(peakX,peakY)*threshold) {xmin = i-(peakX-i); break;}
  }
  if(xmin < 0) xmax = 0;

  // +y
  for(int j(peakY); j < height; j++){
    if(img(peakX,j) < img(peakX,peakY)*threshold) {ymax = j+(j-peakY); break;}
  }
  if(ymax == 0) ymax = height-1; // default to full image size
  if(ymax > height-1) ymax = height-1;

  // -y
  for(int j(peakY); j >= 0; j--){
    if(img(peakX,j) < img(peakX,peakY)*threshold) {ymin = j-(peakY-j); break;}
  }
  if(ymin < 0) ymax = 0;
}

// Weighted sample mean <x> = sum(w_i * x_i) / sum(w_i)
double Cloud::mean(vector<int> * data)
{
  int weightedSum(0), sumWeights(0);;
  for (int i(0); i < data->size(); i++) weightedSum += (*data)[i]*i;
  for (int i(0); i < data->size(); i++) sumWeights += (*data)[i];
  return weightedSum /(double) sumWeights;
}

// Sample variance var_x = sigma^2 = sum(w(x-<x>)^2)/sum(w)
double Cloud::var(vector<int> * data, double mean)
{
  //cout << "Mean = " << mean << endl;
  //for (int i(0); i < data->size(); i++) cout << i << "\t" << data->at(i) << endl;

  double varSum(0), sumWeights(0);
  for (int i(0); i < data->size(); i++) varSum += data->at(i)*(i-mean)*(i-mean);
  for (int i(0); i < data->size(); i++) sumWeights += data->at(i);
  return varSum /(double) sumWeights;
}

// Getters
double Cloud::getMeanX() {return meanX;}
double Cloud::getMeanY() {return meanY;}
double Cloud::getVarX() {return varX;}
double Cloud::getVarY() {return varY;}
int Cloud::getPeakX() {return peakX;}
int Cloud::getPeakY() {return peakY;}
int Cloud::getXmin() {return xmin;}
int Cloud::getXmax() {return xmax;}
int Cloud::getYmin() {return ymin;}
int Cloud::getYmax() {return ymax;}
int Cloud::getPx(int x, int y) {return img(x,y);}

void Cloud::printImg(){
  for (int i(0); i < width; i++)
  {
    for(int j(0); j < height; j++)
    {
      std::cout << i << "\t" << j << "\t" << img(i,j) << std::endl;
    }
  }
}
