#include <iostream>
#include <cmath>

using namespace std;

// Joe Heffer
// Tutorial 2, question 1
// Cartesian vectors

// declare functions
// pass by value (copy method---no pointers used)
float dotProduct(float a[],float b[]);
float * crossProduct(float a[],float b[]);	// this function returns an array i.e. pointer
float angle(float a[],float b[], int c=0);

int main(){

	// two vectors with three components
	float vec1[3] = {1,1,1};
	float vec2[3] = {3,4,5};

	cout << "vec1 = ("<<vec1[0]<<","<<vec1[1]<<","<<vec1[2]<<")\n";
	cout << "vec2 = ("<<vec2[0]<<","<<vec2[1]<<","<<vec2[2]<<")\n";

	cout << "Scalar product = " << dotProduct(vec1,vec2) << "\n";
	float * cross = new float[3];
	cross = crossProduct(vec1,vec2);
	cout << "Vector product = " << cross[0] << "," << cross[1] << "," << cross[2] << "\n";
	cout << "Angle between = " << angle(vec1,vec2) << " radians\n";

	return 0;
}

// define functions

// modulus
float mod(float a[]){
	float x = sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
	return x;
}

// scalar product
float dotProduct(float a[], float b[]){
	// scalar product of two 3-vectors
	float dot = a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
	return dot;
}

// vector product
float * crossProduct(float a[], float b[]){
	float * x = new float[3];
	x[0] = a[1] * b[2] - a[2] * b[1];
	x[1] = a[2] * b[0] - a[0] * b[2];
	x[2] = a[0] * b[1] - a[1] * b[0];
	return x;
}

// angle
float angle(float a[], float b[], int c){
	float x = dotProduct(a,b) / (mod(a) * mod(b));
	if(c){	// degrees
		x = acos(x) * 180 / 3.14;
	} else {// radians
		x = acos(x);
	}
	return x;
}
