/* Author: Joe Heffer jheffer@hep.liv.ac.uk

Unfolds Fabry-Perot interferometer resonances
from a signal taken from an oscilloscope.

The response function (usually peak) should be
shifted leftwards to the first non-zero bin.

"The Gold deconvolution algorithm proves to work
very well, other methods (Fourier, VanCittert 
etc) oscillate." -- Root manual

We don't need the multi-resonance Unfolding method
(used for nuclear resonance spectroscopy,)
the one-dimensional deconvolution method will suffice.
*/

#include "TSpectrum.h";	// This class contains advanced
			// spectra processing functions
			// e.g. one-dimensional deconvolution.
#include "TFile.h";	// Root-file access
#include "TH1.h"	// Histograms
//#include "TPad.h"
#include "THistPainter.h"

void Unfold(){

	// Variables and histograms
	Int_t i;		// counter

	Double_t nbins = 40;	// number of data points
	xmin = 0;		// horizontal axis minimum
	xmax = 40;		// maximum

	Float_t * source = new float[nbins]	// convolved signal from scope
	Float_t * resonances = new float[nbins]	// Fabry-Perot cavity resonances
	Float_t * specArr = new float[nbins]	// modulated laser spectrum

	TH1F * sourHist = new TH1F("sourHist", "Source", nbins, xmin, xmax);
	TH1F * resoHist = new TH1F("resoHist", "Resonances", nbins, xmin, xmax);
	TH1F * specHist = new TH1F("spectrum", "Spectrum", nbins, xmin, xmax);

	// TSpectrum object does the deconvolution
	TSpectrum *spectrum = new TSpectrum();

	// Deconvolution settings
	int_t nIter = 1000;	// number of iterations (Gold algorithm)
	int_t nRep = 1;		// number of repetitions
	int_t Boost = 1;	// boost

		// After every numberIterations one can apply boosting
		// operation (exponential function with exponent given by
		// boost coefficient) and repeat it numberRepetitions times. 

	// Read root file
	TFile * MyData = new TFile("scope-data.root");
	gFile = MyData; // global default file
	// Check file-open OK
	if ( MyData->IsOpen() ) printf("File opened successfully\n");

	// Get source data from the ROOT file to a histogram
	sourHist = (TH1F*) MyData->Get("source;1");

	// Transfer source data from histogram to an array
	for (i=0;i<nbins;i++) source[i] = sourHist->GetBinContent(i+1);

	// Get resonances data from the ROOT file to a histogram
	sourHist = (TH1F*) MyData->Get("source;1");

	// Transfer resonance data from histogram to an array
	for (i=0;i<nbins;i++) resonances[i] = resoHist->GetBinContent(i+1);

	// Close file access
	MyData->Close();

	// Make up some data
	source = {0,0,0,0,0,1,4,16,32,64,128,256,128,64,32,16,8,4,2,1,0,0,1,8,32,128,32,8,1,0};
	resonances = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.4,5.4,24.2,39.9,24.2,5.4,0.4,0,0,0,0,0,0,0}
	for (i=0;i<nbins;i++) spectrum[i] = 

	// Deconvolve (unfold)
	specArr[i] = source[i];
	spectrum->Deconvolution(specArr,resonances,nbins,nIter,nRep,Boost);

		// On successful completion it returns 0.
		// On error it returns pointer to the string describing error.
		// The result is placed in the first parameter, 'spectrum'.

	// Put the unfolded spectrum into a histogram
	for (i=0;i<nbins;i++) specHist->SetBinContent(i+1,specArr[i]);

	// Draw the spectrum histogram
	specHist->Draw();
}
