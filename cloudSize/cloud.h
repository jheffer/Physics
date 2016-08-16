#ifndef CLOUD_H
#define CLOUD_H

#include "CImg.h"
#include <vector>

using namespace std;
using namespace cimg_library;

// My class
class Cloud {
  private:
    CImg<float> img; // the image data
    vector<int> xAxis; // "flattened" data, ROI only
    vector<int> yAxis;
    int width; // image size
    int height;
    int xmin; // roi
    int xmax;
    int ymin;
    int ymax;
    int peakX; // brightest pixel
    int peakY;
    double meanX; // cloud properties
    double meanY;
    double varX;
    double varY;
  public:
    // Data
    Cloud(char * bmpFile);
    void printImg(); // spit out data
    void calcPeak();
    void calcROI();
    int getPx(int x, int y); // return pixel value
    void subBg(); // subtract backgrounds
    // Stats
    double mean(vector<int> * data); // weighted sample mean
    double var(vector<int> * data, double mean); // variance
    // Getters
    int getPeakX();
    int getPeakY();
    double getMeanX(); // get weighted sample mean
    double getMeanY();
    double getVarX(); // weighted sample variance
    double getVarY();
    int getXmin();
    int getXmax();
    int getYmin();
    int getYmax();
};

#endif
