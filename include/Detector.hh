#ifndef Detector_h
#define Detector_h 1

#include "G4VSensitiveDetector.hh"
#include "DetectorHit.hh"
class G4Step;
class G4HCofThisEvent;
class Detector : public G4VSensitiveDetector
{
public:
Detector(const G4String& name,const G4String& HCname);
virtual ~Detector();
virtual void Initialize(G4HCofThisEvent* hc);
virtual G4bool ProcessHits(G4Step* step,G4TouchableHistory*);
virtual void EndOfEvent(G4HCofThisEvent*);
private:
detectorHC* _detectorHC;
};
#endif