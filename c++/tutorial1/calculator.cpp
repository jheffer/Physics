#include <iostream>

using namespace std;

// Joe Heffer -- Tut 1, Problem 1

main() {

  // get numbers
  float a, b;
  cout << "Give me two numbers:\n";
  cin >> a; cin >> b // "backwards" insertion operators

  // get operation // comment needs two slashes
  int choice;
  cout << "What operation would like to do?\n";
  cout << "1 - add\n2 - subtract\n3 - multiply\n4 - divide\n";
  cin >> choice;

  int result;
  if (choice == 1) { // = is assignment, == is comparitor
    result = a + b; // wrong operator
  }
  if (choice = 2) {
    result = a - b;
  }
  if (choice = 3) {
    result = a * b;
  }
  if (choice = 4) {
    result = a + b;
  } else {
    cout >> "Option does not exist\n";
  }
  cout << "result = " << endl;

  return 0;
}
