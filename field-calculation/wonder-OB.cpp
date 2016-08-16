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
const double probe_start = 0.345;
const double probe_end = 0.445;
const int Zprobe_points = 80;
const double Zprobe_start = 0.4;
const double Zprobe_end = 1.2;
const int integrating_factor = 1e3;

const double Ix(16.15);
const double Iy(0.68);
const double Iz(-24.69);
const double lengthX(0.79);
const double lengthY(0.79);
const double lengthZ(1.8);

const double Zwidth(0.83);
const double Zheight(0.557);
const double Zposition(0.49);


int main(){


	//create a cuboid of coil x and y only
	vect a(0,0,0),b(lengthX,0,0),c(0,lengthY,0),d(lengthX,lengthY,0),e(0,0,lengthZ),f(lengthX,0,lengthZ),g(0,lengthY,lengthZ),h(lengthX,lengthY,lengthZ);
	current x11(a,e,Ix),x12(e,g,Ix),x13(g,c,Ix),x14(c,a,Ix),x21(b,f,Ix),x22(f,h,Ix),x23(h,d,Ix),x24(d,b,Ix);
	current y11(a,b,Iy),y12(b,f,Iy),y13(f,e,Iy),y14(e,a,Iy),y21(c,d,Iy),y22(d,h,Iy),y23(h,g,Iy),y24(g,c,Iy);
	
	//create a lower smaller set of z coils
	vect Za(0,0,Zposition),Zb(Zwidth,0,Zposition),Zc(0,Zwidth,Zposition),Zd(Zwidth,Zwidth,Zposition),Ze(0,0,Zposition+Zheight),Zf(Zwidth,0,Zposition+Zheight),Zg(0,Zwidth,Zposition+Zheight),Zh(Zwidth,Zwidth,Zposition+Zheight);
	current z11(Za,Zb,Iz),z12(Zb,Zd,Iz),z13(Zd,Zc,Iz),z14(Zc,Za,Iz),z21(Ze,Zf,Iz),z22(Zf,Zh,Iz),z23(Zh,Zg,Iz),z24(Zg,Ze,Iz);


	//write the field out around the centre of the wire, in plane perpendicular to it.
	ofstream file;
	file.open("CancelField.txt");

	vect X, P;
	double probe_step ((probe_end-probe_start)/double(probe_points));
	double Zprobe_step ((Zprobe_end-Zprobe_start)/double(Zprobe_points));


	for (int i(0); i < probe_points; i++){
		for (int j(0); j < probe_points; j++){
			for( int k(0); k < Zprobe_points; k++) {
				X.setVect(probe_start+i*probe_step,probe_start+j*probe_step,Zprobe_start+k*Zprobe_step);
				//X.setVect(0.5,probe_start+lengthY*j*probe_step,probe_start+lengthZ*k*probe_step);
				P.setVect(184.926e-7,7.77e-7,455.836e-7);
				field probe(X,P);

				probe.AddCurrent(x11,integrating_factor);
				probe.AddCurrent(x12,integrating_factor);
				probe.AddCurrent(x13,integrating_factor);
				probe.AddCurrent(x14,integrating_factor);
				probe.AddCurrent(x21,integrating_factor);
				probe.AddCurrent(x22,integrating_factor);
				probe.AddCurrent(x23,integrating_factor);
				probe.AddCurrent(x24,integrating_factor);

				probe.AddCurrent(y11,integrating_factor);
				probe.AddCurrent(y12,integrating_factor);
				probe.AddCurrent(y13,integrating_factor);
				probe.AddCurrent(y14,integrating_factor);
				probe.AddCurrent(y21,integrating_factor);
				probe.AddCurrent(y22,integrating_factor);
				probe.AddCurrent(y23,integrating_factor);
				probe.AddCurrent(y24,integrating_factor);

				probe.AddCurrent(z11,integrating_factor);
				probe.AddCurrent(z12,integrating_factor);
				probe.AddCurrent(z13,integrating_factor);
				probe.AddCurrent(z14,integrating_factor);
				probe.AddCurrent(z21,integrating_factor);
				probe.AddCurrent(z22,integrating_factor);
				probe.AddCurrent(z23,integrating_factor);
				probe.AddCurrent(z24,integrating_factor);

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
