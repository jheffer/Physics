#include <iostream>

using namespace std;

// Joe Heffer -- Tut 1, Problem 1

int main() { // no type declared

  // get numbers
  float a, b;
  cout << "Give me two numbers:\n";
  cin >> a; cin >> b; // "backwards" insertion operators // missing ;

  // get operation // comment needs two slashes
  int choice;
  cout << "What operation would like to do?\n";
  cout << "1 - add\n2 - subtract\n3 - multiply\n4 - divide\n";
  cin >> choice;

  int result;
  if (choice == 1) { // = is assignment, == is comparitor
    result = a + b; // wrong operator
  }else if (choice == 2) {  // logical structure
    result = a - b;
  }else if (choice == 3) { 
    result = a * b;
  }else if (choice == 4) { 
    result = a / b; // wrong operator
  }else{
    cout << "Option does not exist\n"; // backwards <<
  }
  cout << "result = " << result << endl; // missing variable

  return 0;
}
