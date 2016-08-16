#include <iostream>
#include <iomanip>	// std::setprecision

using namespace std;

// Joe Heffer jheffer@liv.ac.uk
// Calculate the atom number from the fluorescence of a MOT
// N = (Total 4pi flux)/(One-atom flux)

int main() {

  // constants
  const double hv = 2.546E-19;	// energy per photon @ 780 nm, J
  //const double Gamma = 38.117E6;	// Linewidth/Hz, Rb85 D2 line
  const double Gamma = 10E6;	// Linewidth/Hz, Rb85 F = 3 to F' = 4 transition
  const double Isat = 16.6932;	// Saturation intensity, W/m^2
  const double pi(3.1415926);
  
  // laser variables
  double P(50E-3);	// input laser power / W (total all six beams)
  double det(10E6);	// Detuning frequency / Hz
  double d(5E-3);	// Beam diameter / m
  double I(0);	// Laser beam intensity / W/m^2
  double rate(0);	// scattering rate / Hz

  // measurement variables
  double N(0);	// N
  double D(16E-3);	// Detection diameter / m
		// Power meter active surface size
  double R(80E-3);	// Distance from MOT to detector / m
  //double CCDfactor(0);	// CCD calibration / W
  double fluxBg(847E-9);	// Laser fluorescence background (magnet off)/W
  double fluxMeas(1343E-9);	// Measured signal flux (magnet on)/W
  double fluxTotal(0);	// Signal 4pi flux/W

  // calculate scattering rate
  I = P/(pi*(d/2)*(d/2)); // Is this the correct intensity calculation for 6 orthogonal beams?
  rate = (Gamma/2)*(I/Isat)/(1+4*(det/Gamma)*(det/Gamma)+(I/Isat));

  // Calculate 4pi flux
  double fracArea = ((pi*(D/2)*(D/2))/(4*pi*R*R)); // fractional area of power meter over 4pi surface
  fluxTotal = (fluxMeas - fluxBg) / fracArea; // flux / fractional area
  
  // Atom number = 4pi signal flux / one atom flux
  N = fluxTotal / (rate*hv);

  // print results

  cout << setprecision(3);
  cout << "Input power\t" << P*1E3 << " mW\n";
  cout << "Detuning freq.\t" << det*1E-6 << " MHz\n";
  cout << "Beam diameter\t" << d*1E3 << " mm\n";
  cout << "Laser intensity\t" << I*1E3*1E-4 << " mW/cm^2\n";
  cout << "Scattering rate\t" << rate*1E-6 << " MHz\n";
  cout << "I/I_sat\t\t" << I/Isat << endl;
  cout << "Signal flux\t" << (fluxMeas - fluxBg)*1E9 << " nW\n";
  cout << "Fractional area\t" << fracArea*100 << "%\n";
  cout << "4pi flux\t" << fluxTotal << " W\n";
  cout << "N\t\t" << N*1E-6 << " million\n";

  return 0;
}
