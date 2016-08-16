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
	//cout << "software loading " << endl;
	

    ifstream myfile;
    myfile.open("Images/mot_infomation.txt");
    int Mot_X; int Mot_Y; myfile >> Mot_X >> Mot_Y; 
   
    
	string bitmapfile(argv[1]);
		if(argc<2) 
		{// quit if no arguments
		cout << "Error: no file specified." << endl;
		return 0; // quit
		}
			
	// load image
	CImg<unsigned char> src(bitmapfile.c_str());
	int width = src.width();
    	int height = src.height();
		
	
	////////////////////////////////////////////////////////////////////////////////////////////////////
					  //sum rows
	int row_sum[120] = {0}; 
	
	for (int y = 0; y < height ; y++)
	{
		for (int x = 0; x < width; x++)
		{
		  row_sum [y] = row_sum [y] + src(x,y);
		}
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////
					    //sum col
	int col_sum[120] = {0}; 
	
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
		  col_sum [x] = col_sum [x] + src(x,y);
		}
	}

	
	
	/////////////////////////////////////////////////////////////////////////////////////////////////
	// find peak x
	int peak_value = 0;
	int peak_x  = 0;
	
	for (int x = 0; x < width; x++)
	{
	  if(row_sum[x] > peak_value)
	  { peak_value = row_sum[x];
	    peak_x = x;
	  }
	}
	
	/////////////////////////////////////////////////////////////////////////////////////////////////
	// find peak y
	peak_value = 0;
	int peak_y  = 0;
	
	for (int y = 0; y < width; y++)
	{
	  if(col_sum[y] > peak_value)
	  { peak_value = col_sum[y];
	    peak_y = y;
	  }
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////
	// find peak FWHM for x
	int upper_x = 0;
	bool check = false;
	for (int x = peak_x; x < width; x++)
	{
		
	  
	    if(row_sum[x] < (0.5*row_sum[peak_x] ) && check == false)
	    {
	      check = true ;
	      upper_x = x ;
	    }
	  
	}
	int x_FWHM = upper_x - peak_x;
	
	/////////////////////////////////////////////////////////////////////////////////////////////////
	// find peak FWHM for y
	int upper_y = 0;
	check = false;
	for (int y = peak_y; y < height ; y++)
	{
		
	  
	    if(col_sum[y] < (0.5*col_sum[peak_y] ) && check == false)
	    {
	      check = true ;
	      upper_y = y ;
	    }
	  
	}
	int y_FWHM = upper_y - peak_y ;
	
	////////////////////////////////////////////////////////////////////////////////////////////////////
	//setting up file name
	cout << argv[1] << endl;
	string image_filename = argv[1];
	string outFile = image_filename;

	//cout << outFile << endl;
	// Images/5ms/5ms/image_cam_3_001.bmp >>> Images/5ms/5ms/Background_removed/image_cam_3_001.bmp

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
	

	string newfilename = folderdir + molasses_length + flash_time  + outFile;
	
	cout << newfilename << endl;
	//offset_image.save(newfilename.c_str());
	
	
	////////////////////////////////////////////////////////////////////////////////////////////////////
	// writting x-projection to file
	
	molasses_length = molasses_length.substr(0, molasses_length.size()-1);
	flash_time = flash_time.substr(0, flash_time.size()-1);
	string saving_filename_x =  "Images/" + molasses_length + "_" + flash_time + "_" + "MOT_infomation";
	ofstream datafilex;
	datafilex.open(saving_filename_x.c_str());
	
	 cout << saving_filename_x << endl;
	
	 datafilex << peak_x << "\n";
	 datafilex << peak_y << "\n";
	 datafilex << x_FWHM << "\n";
	 datafilex << y_FWHM << "\n";
	 datafilex << "peak_x" << "\n";
	 datafilex << "peak_y" << "\n";
	 datafilex << "x_FWHM" << "\n";
	 datafilex << "y_FWHM" << "\n";
	 
	

	return 0;
}


