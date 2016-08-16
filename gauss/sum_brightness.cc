//C++ headers
#include<iostream>
#include<sstream>
#include<fstream>
#include<cmath>
#include<iomanip>

//Root headers
#include "CImg.h"

//namespaces
using namespace std;
using namespace cimg_library;

// Adds up how much pixel intensity is above a threshold
// inside a ROI around the MOT centre

float Guassian (float x, float a, float b, float c, float d)
{
  float y;
  y = a * exp(-pow(x - b,2.0) / (2 * pow(c,2))) + d;
  return y;
}

int main(int argc, char* argv[])
{
  // Command line arguments
  if(argc<2) // quit if no arguments
  {
    cout << "Error: no file specified." << endl;
    return 0; // quit
  }
  string bitmapfile(argv[1]);
  string motInfoFile(argv[2]);

  // load MOT info from file
  ifstream myfile;
  myfile.open(motInfoFile.c_str());
  int sizeX, sizeY, peakX, peakY, sigX, sigY, xmin, xmax, ymin, ymax;
  myfile >> sizeX >> sizeY >> peakX >> peakY >> sigX >> sigY >> xmin >> xmax >> ymin >> ymax;
  //cout << "[" << xmin << ":" << xmax << "]\n";
  //cout << "[" << ymin << ":" << ymax << "]\n";

  // constants
  const int cut_threshold = 0;
      
  // load image
  CImg<unsigned char> src(bitmapfile.c_str());
  int width = src.width();
  int height = src.height();
  //cout << "Image dimensions: " << width << "x" << height << endl;

  // variables
  int cut_Brightness_sum = 0; // how much pixel value has been cut
  int value = 0; // pixel value
  int Above_threshold = 0; // count how many pixels are above threshold

  // Loop over MOT pixels
  for (int x = xmin; x <= xmax; x++)
  {
    for (int y = ymin; y <= ymax; y++)
    {
      value = src(x,y); // value of pixel at this point
      if (value > cut_threshold) // if pixel value is above threshold
      {
        cut_Brightness_sum += value; // sum up how much pixel value has been cut
        Above_threshold++;
      }
    }
  }

  cout <<  cut_Brightness_sum  << "\t" << Above_threshold << endl;
  return 0;
}
