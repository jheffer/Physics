#include <iostream>
#include "CImg.h" // to load bitmaps

using namespace std;
using namespace cimg_library;

// Declare functions
int sumPx(CImg<float> img, int xmin, int xmax, int ymin, int ymax); // sum pixels
void usage(); // help

int main(int argc, char* argv[])
{

  // Declare variables
  const char * bmpFile; // filename
  int xmin(0),xmax(0),ymin(0),ymax(0); // ROI parameters

  // Process command line arguments
  for(int i(1); i < argc; i++)
  {
    // Set ROI by command line
    if((string)argv[i]=="-x"){ // x-axis ROI limits
      if(i+2>=argc) {usage(); return 0;} // needs 2 limits
      xmin = atoi(argv[++i]);
      xmax = atoi(argv[++i]);
    } else if((string)argv[i]=="-y"){ // y-axis ROI limit
      if(i+2>=argc) {usage(); return 0;}
      ymin = atoi(argv[++i]);
      ymax = atoi(argv[++i]);
    } else {
    bmpFile = argv[i]; // filename
    }
  }
  if(argc==1){usage();} // give instructions if no commands

  // Suppress error diaglogue boxes
  cimg::exception_mode(0);

  // Load bitmap from command line argument
  try
  {
    // Load image
    CImg<float> img(bmpFile);
    // Default ROI = image size
    if(xmax == 0) {xmax = img.width();}
    if(ymax == 0) {ymax = img.height();}
    //cout << xmin << " " << xmax << endl;
    //cout << ymin << " " << ymax << endl;
    // Print pixel sum
    cout << sumPx(img,xmin,xmax,ymin,ymax) << endl;
  }
  catch (CImgException)
  { // error handling
    //cout << "Error opening " << bmpFile << endl;
    cout << "0" << endl;
    return 0;
  }

  // end main
  return 0;
}

// Sum pixel values function
int sumPx(CImg<float> img, int xmin, int xmax, int ymin, int ymax)
{
  int sum (0); // running total of pixel intensities
  for (int i(0); i < img.width(); i++) { // loop over columns
    if ((i >= xmin) && (i <= xmax)) { // within x ROI   
      for (int j(0); j < img.height(); j++) { // and rows
        if ((j >= ymin) && (j <= ymax)) { // within y ROI
          sum += img(i,j);
        }
      }
    }
  }
  return sum;
}

// Help page
void usage(){
  cout << "sum [file.bmp]" << endl;
  cout << "'-x' ROI x-axis e.g. -x 200 400" << endl;
  cout << "'-y' ROI y-axis e.g. -y 200 400" << endl;
}
