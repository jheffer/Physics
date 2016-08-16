#include <iostream>

using namespace std;

// Joe Heffer
// Tutorial 2, question 2
// Pointers and references
// Program to convert celsius into fahrenheit

// conversion prototypes
// Pass by reference:
void conversion(int & temperature);	// address of the variable
void conversion(float * temperature);	// pointer to variable (i.e. address of variable)

int main() {
    
  // integer celcius value
  int i_celsius = 22;		// integer variable for temperature
  cout << "Temperature = " << i_celsius << " C\n";

  // perform integer conversion and display result
  conversion(i_celsius);	// pass variable to function

  // float celsius value
  float f_celsius =  22.5;
  cout << "Temperature = " << f_celsius << " C\n";

  // perform float conversion and display result
  conversion(&f_celsius);

  return 0;
}

// Implement functions:

// &integer
void conversion(int& temperature){	// using the real data, not a copy
	float f = temperature * 1.8 + 32;
	cout << "Temperature = " << f << " F\n";
}

// *float
void conversion(float * temperature){
	float f = (*temperature) * 1.8 + 32;	// dereference pointer
	cout << "Temperature = " << f << " F\n";
}
