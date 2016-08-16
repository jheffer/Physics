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
	int row_sum[1280] = {0}; 
	
	for (int y = 0; y < height ; y++)
	{
		for (int x = 0; x < width; x++)
		{
		  row_sum [y] = row_sum [y] + src(x,y);
		}
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////
					    //sum col
	int col_sum[1024] = {0}; 
	
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
		  col_sum [x] = col_sum [x] + src(x,y);
		}
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////
	
	


	////////////////////////////////////////////////////////////////////////////////////////////////////
	//setting up file name
	cout << argv[1] << endl;
	string image_filename = argv[1];
	string outFile = image_filename;
	
	/*
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
	*/
	
	////////////////////////////////////////////////////////////////////////////////////////////////////
	// writting x-projection to file
	
	//molasses_length = molasses_length.substr(0, molasses_length.size()-1);
	string saving_filename_x =  outFile + "-x.txt";
	
	ofstream datafilex;
	datafilex.open(saving_filename_x.c_str());
	
	cout << saving_filename_x << endl;
	for (int x = 0; x < width; x++)
	{
	  datafilex << x <<"\t" << col_sum[x] << "\n";
	}
	datafilex.close();
	
	////////////////////////////////////////////////////////////////////////////////////////////////////
	// writting y-projection to file
	
	//string saving_filename_y =  molasses_length + ".bmp-y.txt";
	string saving_filename_y =  outFile + "-y.txt";
	
	ofstream datafiley;
	datafiley.open(saving_filename_y.c_str());
	
	cout << saving_filename_y << endl;
	for (int y = 0; y < height; y++)
	{
	  datafiley << y <<"\t" << row_sum[y] << "\n";
	}
	datafiley.close();
	
	
	return 0;
}


