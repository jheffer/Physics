#include <iostream>
#include <math.h>	// for pow()
#include <iomanip>	// for setprecision()

using namespace std;

// factorial function
float fac(int n) {	// parameter = integeter to get factorial of
	float fac(n);
	//cout << "n = " << n << endl;

	for(int i(1); i < n; i++){
		fac = fac * (n-i);
		//cout << "i = " << i << "\t(n-i) = " << (n-i) << "\tfac = " << fac << endl;
	}

	return fac;
}

int main(){

	float p(0.5);	// success probability 50%
	int k(0);	// number of successes
	int n(1);	// number of trials

	cout << "How many times will you flip the coin?\n";
	cin >> n;
	
	cout << "How many heads do you want to see?\n";
	cin >> k;

	if(k > n){
		cout << "Error: greater number of heads than flips!\n";
		return 0;
	}

	// binomial coefficient
	float bin = fac(n) / (fac(k) * fac(n-k));
	
	// probability mass function
	float prob = bin * pow(p,k) * pow(1-p,n-k);
	cout << setprecision(2) << "Probability = " << prob * 100 << "%" << endl;

	return 0;
}
