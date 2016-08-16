// Molasses cloud position and size
//
// Finds the mean position and variance of a 2D array of numbers
// i.e. molasses position using cloud class, which processes BMPs.
//
// jheffer@liv.ac.uk

#include <iostream>
#include "cloud.h"

using namespace std;

void usage(); // help

int main(int argc, char* argv[])
{
  if(argc==1) usage(); // show help if no arguments
  cimg::exception_mode(0); // suppress error diaglogue boxes

  try
  {
    Cloud myCloud(argv[1]); // load specified bitmap

    // print results
    //cout << "Peak = (" << myCloud.getPeakX() << "," << myCloud.getPeakY() << ")" << endl;
    //cout << "ROI = [" << myCloud.getXmin() << ":" << myCloud.getXmax() << "] [";
    //cout << myCloud.getYmin() << ":" << myCloud.getYmax() << "]" << endl;
    //cout << "<x> = " << myCloud.getMeanX() << "\tStDev_x = " << sqrt(myCloud.getVarX()) << endl;
    //cout << "<y> = " << myCloud.getMeanY() << "\tStDev_y = " << sqrt(myCloud.getVarY()) << endl;
    cout << myCloud.getXmin() << "\t" << myCloud.getXmax() << "\t";
    cout << myCloud.getYmin() << "\t" << myCloud.getYmax() << "\t";
    cout << myCloud.getMeanX() << "\t" << sqrt(myCloud.getVarX());
    cout << "\t" << myCloud.getMeanY() << "\t" << sqrt(myCloud.getVarY()) << endl;
  }
  catch (CImgException) // error handling
  {
    cout << "Error opening " << argv[1] << endl;
    return 0;
  }

  // end main
  return 0;
}

// Help page
void usage(){
  cout << "gauss [FILE]" << endl;
  cout << "Gives ROI, cloud position (weighted mean) and standard deviation." << endl;
  cout << "Output: xmin xmax ymin xmax <x> StDv_x <y> StDv_y" << endl;
}
