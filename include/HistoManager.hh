#ifndef HistoManager_h
#define HistoManager_h 1

#include "globals.hh"

class TFile;
class TH1D;

class HistoManager
{
public:
 HistoManager();
~HistoManager();

void Book();
void Save();
void Draw();
void Fill(std::tuple<G4double,G4double>);

void Set_Photons_Energy(G4double);
void Set_Neutron_Energy(G4double);
void Set_Number_Of_Produced_Electron(G4double /*energy*/);

private:
G4double _CT;
G4double _edep;

TH1D* _histo_neutron; 
TH1D* _histo_photons;
TH1D* _histo_number_of_produced_electron ;

TFile* rootfile;


};
#endif
