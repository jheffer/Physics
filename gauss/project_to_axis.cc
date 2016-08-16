// C++ headers
#include<iostream>
#include <vector>

// ROOT headers
#include "CImg.h"

// namespaces
using namespace std;
using namespace cimg_library;

int main(int argc, char* argv[])
{
  // quit if no arguments
  if(argc<2) 
  {
    cout << "Error: no file specified." << endl;
    return 0; // quit
  }
  string bitmapfile(argv[1]);
  string xy("x");
  if (argv[2] != NULL) xy = argv[2];

  // load bitmap
  CImg<unsigned char> img(bitmapfile.c_str());
  int width = img.width();
  int height = img.height();

  // project to axes
  if (xy == "x") // x-axis
  {
    vector<int> xaxis(width);
    int sum = 0;
    for (int x = 0; x < width; x++)
    {
      for (int y = 0; y < height; y++) sum += img(x,y);
      xaxis[x] = sum;
      sum = 0;
    }
  for (int i(0); i < width; i++) cout << i << "\t" << xaxis[i] << endl; // print
  }
  else // y-axis
  {
    vector<int> yaxis(height);
    int sum = 0;
    for (int y = 0; y < height; y++)
    {
      for (int x = 0; x < width; x++) sum += img(x,y);
      yaxis[y] = sum;
      sum = 0;
    }
  for (int j(0); j < width; j++) cout << j << "\t" << yaxis[j] << endl; // print
  }

  return 0;
}
