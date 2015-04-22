#ifndef fftHelper_hh
#define fftHelper_hh 1
//C++ INCLUDES
//ROOT INCLUDES
#include "TVirtualFFT.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TH1F.h"
#include "TString.h"
//LOCAL INCLUDES

TH1F* GetFirstTransform( TH1F* input, float sf, TString name = "" );
bool  FillHisto( TF1* f, TH1F* h );

#endif
