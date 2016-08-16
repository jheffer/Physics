#include <iostream>

using namespace std;

// Joe Heffer Problem 1.4

int main() {
	int terms(10);		// number of terms to calculate
	double fibTot(0);	// sum total

	cout << "How many Fibonacci terms to calculate?\n";
	cin >> terms;
	double fibSeq[terms];	// array for entire sequence

	// loop until specified number of terms reached
	for(int i(0); i < terms; i++){

		// use seed number for first two terms,
		if (i == 0) fibSeq[i] = 0;
		if (i == 1)  fibSeq[i] = 1;

		// thereafter add the previous two terms in the sequence
		if(i > 1) fibSeq[i] = fibSeq[i-1] + fibSeq[i-2];

		// running total
		fibTot = fibTot + fibSeq[i];

		// print results
		cout << "Fibonacci(" << i << ") = " << fibSeq[i]	// fibonacci number
		<< "\tSum("<<i<<") = " << fibTot << endl;		// running total
	}

	return 0;
}
