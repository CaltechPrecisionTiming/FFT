//C++ INCLUDES
#include <iostream>
//ROOT INCLUDES
//LOCAL INCLUDES
#include "fftHelper.hh"

TH1F* GetFirstTransform( TH1F* input, float sf , TString name )
{
  TH1 *hm =0;
  TVirtualFFT::SetTransform(0);
  hm = input->FFT( hm, "MAG_" + name );
  hm->SetTitle("Magnitude of the 1st transform");
  int n_bin_fft = hm->GetNbinsX();
  float range = (float)n_bin_fft/( input->GetXaxis()->GetBinUpEdge( n_bin_fft ) - input->GetXaxis()->GetBinLowEdge( 1 ) );
  range *= sf;
  TH1F* hmr = new TH1F( "hmr_" + name,"Magnitude of the 1st transform", n_bin_fft, 0, range);
  for( int i = 1; i <= n_bin_fft; i++)
    {
      double bc = hm->GetBinContent( i )/sqrt( (float)n_bin_fft );
      hmr->SetBinContent( i, bc );
    }
  hmr->SetXTitle("f (MHz)");
  return hmr;
};

bool  FillHisto( TF1* f, TH1F* h )
{
  int n = h->GetNbinsX();
  float x;
  float range = h->GetXaxis()->GetBinUpEdge( n ) - h->GetXaxis()->GetBinLowEdge( 1 );
  for ( int i = 0; i < n; i++ )
    {
      x = range*( (float) i )/( (float) n);
      h->SetBinContent( i, f->Eval(x) );
    }
  return true;
};
