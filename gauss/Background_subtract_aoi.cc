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

int main(int argc, char* argv[])
{
  // Command line arguments
  if(argc<2) // quit if no arguments
  {
    cout << "Error: no file specified" << endl;
    return 0; // quit
  }
  string bitmapfile(argv[1]);
  string motInfoFile(argv[2]);

  // load MOT info
  ifstream myfile;
  myfile.open(motInfoFile.c_str());
  int sizeX, sizeY, peakX, peakY, sigX, sigY, xmin, xmax, ymin, ymax;
  myfile >> sizeX >> sizeY >> peakX >> peakY >> sigX >> sigY >> xmin >> xmax >> ymin >> ymax;
  //cout << "ROI-x [" << xmin << ":" << xmax << "]\n";
  //cout << "ROI-y [" << ymin << ":" << ymax << "]\n";

  // load image
  CImg<unsigned char> src(bitmapfile.c_str());
  int width = src.width();
  int height = src.height();

  CImg<unsigned char> offset_image;
  offset_image = src;

  // average between rows .offsets. to fix stripe
  float row_average = 0;
  float offsets_row [120] = {0};
  for (int y = ymin; y <= ymax; y++)
  {
    for (int x = 0; x < 30 ;x++)
    {
      row_average += src(x,y) ;
    }
    offsets_row[y] = row_average / 30.0 ;
    row_average = 0;
  }
  
  // correct "stripe" effect
  int scr_value = 0;
  int ofset_value = 0;
  int offset_pixel = 0;
  for (int y = ymin; y <= ymax; y++)
  {
    for (int x = xmin; x <= xmax; x++)
    {
      scr_value = src(x,y);
      ofset_value = (int ) offsets_row[y];
      if (scr_value < ofset_value){
        offset_pixel=0;
      } else {  
        offset_pixel = scr_value - ofset_value;
      }
      offset_image(x,y) = offset_pixel;
    }
  }

  string outFile = bitmapfile;
  string delimiter = "/";
  int i = 0;

  // file directory
  i = outFile.find(delimiter);
  string folderdir = outFile.substr(0, i+1); 
  outFile.erase(0, folderdir.length());

  // molasses_length
  i = outFile.find(delimiter);
  string molasses_length = outFile.substr(0, i+1); 
  outFile.erase(0, molasses_length.length());

  // flash_time
  i = outFile.find(delimiter);
  string flash_time = outFile.substr(0, i+1); 
  outFile.erase(0, flash_time.length());

  // save output bitmap file
  string newfilename = folderdir + molasses_length + flash_time + "Background_removed/" + outFile;
  offset_image.save(newfilename.c_str());
  
  return 0;
}
