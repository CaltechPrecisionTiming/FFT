//C++ INCLUDES
#include <iostream>
//ROOT INCLUDES
#include "TH1D.h"
#include "TVirtualFFT.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TMath.h"
//Local Includes
#include "T.hh"
#include "fftHelper.hh"

int main( int argc, char** argv )
{

  TFile* fin = new TFile("/Users/cmorgoth/Work/data/LaserDataAtCaltech/02282015/CIT_Laser_022015_69.root");
  TTree* t = (TTree*)fin->Get("T");
  int nentries = t->GetEntries();
  T* tree = new T( t );

  int n_bins   = 1024;
  float x_low  = -0.5;
  float x_high = 1023.5;
  float range = x_high - x_low;
  float sf = 5.0e3;//convert sampling rate into MHz

  //define fitting model
  TF1 *model = new TF1("model", "[0]*exp(-(x-[1])/[2])*TMath::Erfc(-(1/sqrt(2))*((x-[1])/[3] + [3]/[2]))", 0, 1023);
  model->SetParameter( 0, 1. );
  model->SetParameter( 1, 679. );
  model->SetParameter( 2, 40. );
  model->SetParameter( 3, 2. );
  model->SetLineColor( kViolet );

  TF1 *model2 = new TF1("model2", "[0]*exp(-(x-[1])/[2])*TMath::Erfc(-(1/sqrt(2))*((x-[1])/[3] + [3]/[2])) + [4]*sin(2*TMath::Pi()*[5]*x)", 0, 1023);
  model2->SetParameter( 0, 1. );
  model2->SetParameter( 1, 679. );
  model2->SetParameter( 2, 40. );
  model2->SetParameter( 3, 2. );
  model2->SetParameter( 4, 0.05 );
  model2->SetParameter( 5, 2. );
  model2->SetLineColor( kViolet );
  
  //Getting first entry transform
  TH1F* h_tmp = new TH1F( "h_tmp", "h_tmp", n_bins, x_low, x_high );
  h_tmp->Scale( 1.0/h_tmp->Integral() );
  tree->GetHisto( 1, 0, h_tmp );
  h_tmp->Fit( model2, "MLR");
  TH1F* fft_total = new TH1F( *GetFirstTransform( h_tmp, sf, "entry_0" ) );
  //Normalize to number of entries
  fft_total->Scale( 1.0/( (float) nentries ) );
  TH1F* h_sample = new TH1F(*h_tmp);
  h_sample->Fit( model2, "MLR");
  delete h_tmp;
  /*
  tranform of the fit
  */
  //get a histogram first
  TH1F* h_f = new TH1F( "h_f", "h_f", 25000, x_low, x_high );
  FillHisto( model2, h_f );
  TH1F* fft_fit = new TH1F( *GetFirstTransform( h_f, sf, "fit" ) );
  
  //Loop over n-1 remaining entries
  for ( int i = 1; i < nentries; i++ )
    {
      TString s_name = TString( Form( "entry_%d", i ) );
      TH1F* h_tmp = new TH1F( "h_tmp_" + s_name, "h_tmp_" + s_name, n_bins, x_low, x_high );
      h_tmp->Scale( 1.0/h_tmp->Integral() );
      tree->GetHisto( 1, i, h_tmp );
      TH1F* fft = new TH1F( *GetFirstTransform( h_tmp, sf, s_name ) );
      fft->Scale( 1.0/( (float) nentries ) );
      fft_total->Add(fft);
      delete h_tmp;
      delete fft;
    }
  /*
  //A function to sample
  TF1 *fsin = new TF1("fsin", "sin(2*TMath::Pi()*x)+sin(4*TMath::Pi()*x)+sin(6*TMath::Pi()*x)", 0, 123);
  fsin->Draw();
  Int_t n=25000;
  TH1F *hsin = new TH1F("hsin", "hsin", n+1, 0, 123);
  Double_t x;
  //Fill the histogram with function values
  for (Int_t i=0; i<=n; i++){
    x = (Double_t(i)/n)*(123);
    hsin->SetBinContent(i+1, fsin->Eval(x));
  }
  
  TH1F* fft_2  = new TH1F( *GetFirstTransform( hsin, 1.0 ) );
  */
  TFile* fout = new TFile( "test_fit.root", "recreate" );
  //h_tmp->Write();
  fft_total->Write();
  fft_fit->Write();
  h_sample->Write();
  //model->Write();
  //fft_2->Write("fft_2");
  fout->Close();

  return 0;
}
