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
	cout << "WORKING!" << endl;
	 ifstream myfile;
	 myfile.open("Images/mot_infomation.txt");
	cout << "Working" << endl;
         int Mot_X; int Mot_Y; 
	cout << "Still working" << endl;
	myfile >> Mot_X >> Mot_Y;
	cout << Mot_X << " " << Mot_Y << endl;
	
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
			
	//make new image
	CImg<unsigned char> img;
	img = src;

	CImg<unsigned char> offset_image;
	offset_image = src;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	// finding average between rows .offsets. to fix stripe
	float row_average = 0;
	float offsets_row [120] ={0};
	for (int y = Mot_Y - 20; y < Mot_Y + 20; y++)
	{
	 
		for (int x = 0; x < 30 ;x++)
		{
		  row_average = row_average + src(x,y) ;
		}
		
		offsets_row[y] = row_average / 30.0 ;
		row_average = 0;
	}
	

	
	////////////////////////////////////////////////////////////////////////////////////////////////////
	// correcting offset stripe effect
	int scr_value = 0;
	int ofset_value = 0;
	int offset_pixel = 0;
	for (int y = Mot_Y - 20; y < Mot_Y + 20; y++)
	{
		for (int x = Mot_X - 20; x < Mot_X + 20; x++)
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
	
      
       ////////////////////////////////////////////////////////////////////////////////////////////////////
        /*
	// finding average between cols .offsets. to fix slope
	float col_average = 0;
	float offsets_col [120] ={0};
	for (int x = Mot_X - 20; x < Mot_X + 20; x++)
	{
	 
		for (int y = 0; y < 30 ;y++)
		{
		  col_average = col_average + offset_image(x,y) ;
		}
		
		offsets_col[x] = col_average / 30.0 ;
		col_average = 0;
	}
	  ////////////////////////////////////////////////////////////////////////////////////////////////////
	// correcting offset stringing effect
	
	scr_value = 0;
	ofset_value = 0;
	offset_pixel = 0;

	for (int y = Mot_Y - 20; y < Mot_Y + 20; y++)
	{
		for (int x = Mot_X - 20; x < Mot_X + 20; x++)
		{
		     scr_value = offset_image(x,y);
		     ofset_value = (int ) offsets_col[x];
		     if (scr_value < ofset_value){
		       offset_pixel=0;
		     } else {  
		     offset_pixel = scr_value - ofset_value;
		     }
		     offset_image(x,y) = offset_pixel;
		  
		}
	}
	
  */
 ////////////////////////////////////////////////////////////////////////////////////////////////////
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
	

	string newfilename = folderdir + molasses_length + flash_time + "Background_removed/" + outFile;
	//cout << newfilename << endl;
	offset_image.save(newfilename.c_str());
	
	return 0;
}


