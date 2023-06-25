#ifndef k1RA_h
#define k1RA_h 1

#include "G4UserRunAction.hh"
#include "G4Accumulable.hh"

class HistoManager;

class k1RA : public G4UserRunAction
{
public:
k1RA(HistoManager* histo);
virtual ~k1RA();
    
virtual void BeginOfRunAction(const G4Run*);
virtual void   EndOfRunAction(const G4Run*);
//define function for accumulate dose
void Add_Collimator_Phantom_Dose(G4double dose){collimator_phantom_dose += dose;collimator_phantom_dose2+=dose*dose;}
void Add_Around_Phantom_Dose(G4double dose){around_phantom_dose += dose;around_phantom_dose2+=dose*dose;}


private:
//Define Accumulables 
HistoManager* _histo;
G4Accumulable<G4double> collimator_phantom_dose=0;
G4Accumulable<G4double> collimator_phantom_dose2=0;
G4Accumulable<G4double> around_phantom_dose=0;
G4Accumulable<G4double> around_phantom_dose2=0;
};


#endif
