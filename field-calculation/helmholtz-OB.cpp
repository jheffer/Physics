//libraries
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <cmath>
#include <fstream>
#include <vector>

using namespace std;

//my header files
#include"constants.h"

const int probe_points = 100;
const double probe_start = -0.49;
const double probe_end = 0.49;
const int integrating_factor = 1e2;

const int circle_points = 100;
const double circle_radius(0.5);
const double I0 = 1.0;

int main(){


	//create a circle of points
	vector<vect> circleZ1;
	for (int i(1); i < circle_points; i++){
		circleZ1.push_back(vect(circle_radius* cos(2*Pi*double(i)/circle_points), circle_radius* sin(2*Pi*double(i)/circle_points), .5*circle_radius));
	}
	vector<vect> circleZ2;
	for (int i(1); i < circle_points; i++){
		circleZ2.push_back(vect(circle_radius* cos(2*Pi*double(i)/circle_points), circle_radius* sin(2*Pi*double(i)/circle_points), -.5*circle_radius));
	}

	vector<vect> circleX1;
	for (int i(1); i < circle_points; i++){
		circleX1.push_back(vect(.5*circle_radius,circle_radius* cos(2*Pi*double(i)/circle_points), circle_radius* sin(2*Pi*double(i)/circle_points)));
	}
	vector<vect> circleX2;
	for (int i(1); i < circle_points; i++){
		circleX2.push_back(vect(-.5*circle_radius,circle_radius* cos(2*Pi*double(i)/circle_points), circle_radius* sin(2*Pi*double(i)/circle_points)));
	}

	vector<vect> circleY1;
	for (int i(1); i < circle_points; i++){
		circleY1.push_back(vect( circle_radius* sin(2*Pi*double(i)/circle_points), .5*circle_radius,circle_radius* cos(2*Pi*double(i)/circle_points)));
	}
	vector<vect> circleY2;
	for (int i(1); i < circle_points; i++){
		circleY2.push_back(vect( circle_radius* sin(2*Pi*double(i)/circle_points), -.5*circle_radius,circle_radius* cos(2*Pi*double(i)/circle_points)));
	}



	//create currents from circles of points
	vector<current> currZ1;
	for (int i(1); i < circle_points-1; i++){
		currZ1.push_back(current(circleZ1[i],circleZ1[i+1],I0));
	}
	currZ1.push_back(current(circleZ1[circle_points-1],circleZ1[0],I0));

	vector<current> currZ2;
	for (int i(1); i < circle_points; i++){
		currZ2.push_back(current(circleZ2[i],circleZ2[i+1],I0));
	}
	currZ2.push_back(current(circleZ2[circle_points-1],circleZ2[0],I0));

	vector<current> currX1;
	for (int i(1); i < circle_points-1; i++){
		currX1.push_back(current(circleX1[i],circleX1[i+1],I0));
	}
	currX1.push_back(current(circleX1[circle_points-1],circleX1[0],I0));

	vector<current> currX2;
	for (int i(1); i < circle_points; i++){
		currX2.push_back(current(circleX2[i],circleX2[i+1],I0));
	}
	currX2.push_back(current(circleX2[circle_points-1],circleX2[0],I0));

	vector<current> currY1;
	for (int i(1); i < circle_points-1; i++){
		currY1.push_back(current(circleY1[i],circleY1[i+1],I0));
	}
	currY1.push_back(current(circleY1[circle_points-1],circleY1[0],I0));

	vector<current> currY2;
	for (int i(1); i < circle_points; i++){
		currY2.push_back(current(circleY2[i],circleY2[i+1],I0));
	}
	currY2.push_back(current(circleY2[circle_points-1],circleY2[0],I0));


	//write the field out around the centre of the wire, in plane perpendicular to it.
	ofstream file;
	file.open("HelmholtzTest.txt");

	vect X, P;
	double probe_step ((probe_end-probe_start)/double(probe_points));

	for (int i(0); i < probe_points; i++){
		for (int j(0); j < probe_points; j++){
			for( int k(0); k < probe_points; k++) {
				X.setVect(probe_start+i*probe_step,probe_start+j*probe_step,probe_start+k*probe_step);
				P.setVect(0.0,0.0,0.0);
				field probe(X,P);

				for (int a(0); a < circle_points; a++){
					probe.AddCurrent(currX1[a],integrating_factor);
					probe.AddCurrent(currX2[a],integrating_factor);
					probe.AddCurrent(currY1[a],integrating_factor);
					probe.AddCurrent(currY2[a],integrating_factor);
					probe.AddCurrent(currZ1[a],integrating_factor);
					probe.AddCurrent(currZ2[a],integrating_factor);
				}

				file << probe.getPos().getX() << "\t" << probe.getPos().getY() << "\t" << probe.getPos().getZ()<< "\t" << probe.getVec().getX()<< "\t" << probe.getVec().getY()<< "\t" << probe.getVec().getZ()  << endl;
				//probe.getPos().operator<<(file);
				//probe.getVec().operator<<(file);
			}
			file << endl;
		}
		file << endl;
		cout << "x position " << probe_start+i*probe_step << endl;
	}

	return 0;

}
