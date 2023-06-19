#ifndef phantomSD_h
#define phantomSD_h 1

#include "G4VSensitiveDetector.hh"
#include "phantomHit.hh"
class G4Step;
class G4HCofThisEvent;
class phantomSD : public G4VSensitiveDetector
{
public:
phantomSD(const G4String& name,const G4String& HCname);
virtual ~phantomSD();
virtual void Initialize(G4HCofThisEvent* hc);
virtual G4bool ProcessHits(G4Step* step,G4TouchableHistory*);
virtual void EndOfEvent(G4HCofThisEvent*);
private:
phantomHC* _phantomHC;
};
#endif