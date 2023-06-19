#include "Detector.hh"
#include "G4VSensitiveDetector.hh"
#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "k1DC.hh"
#include "G4RunManager.hh"
#include "G4ThreeVector.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4Gamma.hh"
#include "G4Neutron.hh"
#include "G4Neutron.hh"
#include "G4Electron.hh"
#include <cmath>

Detector::Detector(const G4String& name,const G4String& HCname):
G4VSensitiveDetector(name),
_detectorHC(NULL)
{
collectionName.insert(HCname);
}
Detector::~Detector(){}
void Detector::Initialize(G4HCofThisEvent* hc)
{
  _detectorHC = new detectorHC(SensitiveDetectorName,collectionName[0]);
  G4int hcID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  hc->AddHitsCollection(hcID,_detectorHC);
}
G4bool Detector::ProcessHits(G4Step* step,G4TouchableHistory*)
{
  if(step->GetTrack()->GetDefinition() == G4Neutron::Neutron())
{  // Neutron Flux
	if(step->GetTrack()->GetMomentumDirection().y()<0)
		return true;
	else 
	{
    auto hc = new DetectorHit();
    G4double Neutron_Energy=step->GetPreStepPoint()->GetKineticEnergy()/MeV;
//    G4cout<<Neutron_Energy<<G4endl;
//    G4cout<<step->GetTrack()->GetMomentumDirection()<<G4endl;
    hc->Set_Neutron_Energy(Neutron_Energy);
    _detectorHC->insert(hc);
	} 
  }
  
return true;
}
void Detector::EndOfEvent(G4HCofThisEvent*)
{
}
