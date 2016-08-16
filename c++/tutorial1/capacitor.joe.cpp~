#include <iostream>
#include <iomanip>

using namespace std;

// Joe Heffer Problem 1.2

int main(){
	float e(8.85e-12);	// vacuum permittivity
	float x(25.4e-2);	// side (m)
	float y(x);		// other side (m)
	float d(0.16e-3);	// distance (m)

	cout << "Enter plate length (cm)\n";
	cin >> x;
	x = x / 100;
	cout << "Enter plate width (cm)\n";
	cin >> y;
	y = y / 100;
	cout << "Enter plate separation (mm)\n";
	cin >> d;
	d = d / 1000;

	float A(x*x);		// area (m^2)
	float C = e * A / d;	// capacitance
	cout << setprecision(3) << "Capacitance = " << C * 1e9 << " nF"<< endl;

	float V(50);	// p.d.
	cout << "Enter potential difference (V)\n";
	cin >> V;
	float Q(C*V);	// charge	
	cout << setprecision(3) << "Charge = " << Q *1e9 << " nC"<< endl;

	return 0;
}
