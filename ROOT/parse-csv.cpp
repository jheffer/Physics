#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "TH1D.h"

// Class for each row of the CVS file

class CVSRow
{
    public:
	// this[i] returns one item in this object's vector m_data
        std::string const& operator[](std::size_t index) const
        {
            return m_data[index];
        }
        std::size_t size() const
        {
            return m_data.size();
        }
        void readNextRow(std::istream& str) // parameter = address of istream, called 'str'
        {
            std::string line;
            std::getline(str,line); // read the line into string 'line'

            std::stringstream   lineStream(line);
            std::string         cell;

            m_data.clear(); // empty the vector
            while(std::getline(lineStream,cell,',')) // read each line into cells separated by ','
            {
                m_data.push_back(cell); // push each cell into this row's vector
            }
        }
    private:
        std::vector<std::string>    m_data; // vector containing each 'cell' in this row
};

std::istream& operator>>(std::istream& str,CVSRow& data)
{
    data.readNextRow(str);
    return str;
}   
int parse()
{
	// variables
	const int numRows = 11000;

	// load CVS file
	std::ifstream myFile("data.csv");

	// array containing rows
	CVSRow myData [numRows];
	int i = 0;
	CVSRow row;

	// read data into an array of CVSRow objects
	while(myFile >> row)
	{
		row.readNextRow(myFile);
		myData[i] = row;
		i++;
		//cout << myData[i][0] << endl;
	}

	// create histogram
	TH1D * h1 = new TH1D("h1", "Circuit output;Time/s;Signal/V", 11000, 1, 11000);

	// fill histogram
	for(int j = 0; j<numRows; j++)
	{
		h1->Fill(myData[i][2], 1);
	}

	// display histogram
	hist1->SetStats(kFALSE);	// disable histogram statistics box
	hist1->SetFillColor(36);
	hist1->SetLineColor(1);
	hist1->Draw();
}
