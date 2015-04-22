#define T_cxx
//C++ INCLUDES
#include <iostream>
//LOCAL INCLUDES
#include "T.hh"
//ROOT INCLUDES
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void T::Loop()
{
  if (fChain == 0) return;
  
  Long64_t nentries = fChain->GetEntriesFast();
  
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    // if (Cut(ientry) < 0) continue;
  }
};

bool T::GetHisto( int channel, int entry, TH1F* h )
{
  //TH1F h("h", "h", 1024, 0, 1024);
  if (fChain == 0) return false;
  fChain->GetEntry( entry );
  for( int j = 0; j < 1024; j++ )
    {
      switch ( channel )
	{
	case 1:
	  h->SetBinContent( j+1, -c1[j] );
	  break;
	case 2:
	  h->SetBinContent( j+1, -c2[j] );
	  break;
	case 3:
	  h->SetBinContent( j+1, -c3[j] );
	  break;
	case 4:
	  h->SetBinContent( j+1, -c4[j] );
	  break;
	}
    }
  
  return true;
};

