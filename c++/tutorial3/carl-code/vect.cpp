#include <iostream>
#include <cmath>
#include "point.h"
#include "vect.h"

using namespace std;

// Source code from Introduction to Programming using C++
// Tutorial 3: Question 1
// vect implementation
// Author: Carl Gwilliam <gwilliam@hep.ph.liv.ac.uk>

// empty constructor
Vect::Vect()
{
} 

// constructor with explicit x,y and z
Vect::Vect(double x, double y, double z)
{
} 

// constructor for vector between two points
Vect::Vect(Point a, Point b) {
} 

// copy constructor
Vect::Vect(const Vect& rhs) {
}

// empty destructor
Vect::~Vect()
{
} 

// dot product
double Vect::dotProduct(const Vect& rhs) const {
}

// vector product
Vect Vect::crossProduct(const Vect& rhs) const {
}

// get angle between two vectors
double Vect::getAngle(const Vect& rhs) const {
}

// magnitude of vector
double Vect::getMagnitude() const {
}

// overload addition operator
Vect Vect::operator+ (const Vect& rhs) {
}

// overload subtraction operator
Vect Vect::operator- (const Vect& rhs) {
}

// overload cross product operator
Vect Vect::operator* (const Vect& rhs) {
}
  
// overload assignment operator
Vect& Vect::operator= (const Vect& rhs) {
}










