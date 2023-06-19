#include "HistoManager.hh"
#include <TH1D.h>
#include <TFile.h>
//there is another way to include following header .
#include <CLHEP/Units/SystemOfUnits.h>
HistoManager::HistoManager():rootfile(0)
{
//  for(int i=0;i<20;i++)_histo_Electrons[i]=0;
  /* 
  
  photon energy :

  for  0.1 < E < 1  keV : E=100(eV) + 100(eV)*i          i: arraye index 0 <=i <= 8 , i is int
  for  1 <= E <= 10 keV : E= 1(keV) + (i-9)(keV)       i: arraye index 8 < i < 20 , i is int
  
  */
_histo_neutron=0;
  _histo_photons=0;
  _histo_number_of_produced_electron=0;
}

HistoManager::~HistoManager(){if(rootfile)delete rootfile;}

void HistoManager::Save()
{
    if(!rootfile)return;
    rootfile->Write();
    rootfile->Close();
}

void HistoManager::Book()
{
//std::string name[20];
//for(int i=0;i<20;i++)name[i]="E "+ std::to_string((i<=8) ? 100+100*i : 1000+1000*(i-9))+"eV";
//rootfile = new TFile("result.root","RECREATE");
//for(int i=0;i<20;i++)_histo_Electrons[i] = new TH1D(name[i].c_str(), "Electrons (eV)", (i<=8) ? 1000 : 10000, 0., (i<=8) ? 1000 : 10000);
_histo_neutron   = new TH1D("neutron", "energy",2450,0,7350);
_histo_photons   = new TH1D("photon", "energy",10000,0,10000);
_histo_number_of_produced_electron   = new TH1D("electrons", "no",10000,0,10000);
}


//photons
void HistoManager::Set_Neutron_Energy(G4double e){_histo_neutron->Fill(e);}
//electrons
void HistoManager::Set_Photons_Energy(G4double e){_histo_photons->Fill(e);}
void HistoManager::Set_Number_Of_Produced_Electron(G4double e){_histo_number_of_produced_electron->Fill(e);}

