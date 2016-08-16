#include <iostream>

using namespace std;

void factors(int x, int showFactors = 0);
void factorsPrime(int x);

// Joe Heffer
// Tutorial 2 problem 4
// Prime factors

int main() {
	int myNumber;
	cout << "Give me a number\n";
	cin >> myNumber;
	//factors(myNumber, 1);
	factorsPrime(myNumber);
}

void factors(int x, int showFactors){
	int nfactors(0);
	if(showFactors) cout << "1 is a factor\n";
	for (int i = 1; i < x; i++) {
		if ((!(x % i)) && (i != 1)) {
			if(showFactors) cout << i << " is a factor\n";
			nfactors++;
		}
	}
	if(showFactors && x > 1) cout << x << " is a factor\n";
	if (!nfactors) cout << x << " is prime\n";
	if (nfactors) cout << x << " has " << nfactors + 2 << " factors.\n";
}

void factorsPrime(int x){
	if(x > 1) cout << "1 is a prime factor\n";
	// factors of x
	for (int i = 1; i < x; i++) {
		if ((!(x % i)) && (i != 1)) {
			//cout << i << " is a factor\n";
			int nfactors = 0; // number of factors of i
			// factors of i (where i is a factor of x)
			for (int j = 1; j < i; j++) {
				if ((!(i % j)) && (j != 1)) nfactors++;
			}
			if(nfactors==0) cout << i << " is a prime factor\n";
		}
	}
}
