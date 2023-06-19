#include "phantomSD.hh"
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
#include "G4Electron.hh"
#include <cmath>

phantomSD::phantomSD(const G4String& name,const G4String& HCname):
G4VSensitiveDetector(name),
_phantomHC(NULL)
{
collectionName.insert(HCname);
}
phantomSD::~phantomSD(){}
void phantomSD::Initialize(G4HCofThisEvent* hc)
{
  _phantomHC = new phantomHC(SensitiveDetectorName,collectionName[0]);
  G4int hcID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  hc->AddHitsCollection(hcID,_phantomHC);
}
G4bool phantomSD::ProcessHits(G4Step* step,G4TouchableHistory*)
{
  if(step->GetTrack()->GetDefinition() == G4Neutron::Neutron())
  {
	if(step->GetTrack()->GetMomentumDirection().y()<0)
		return true;
	else
	{
  // Neutron Flux
    auto hc = new phantomHit();
    G4double Neutron_Energy=step->GetPreStepPoint()->GetKineticEnergy()/MeV;
//    G4cout<<Neutron_Energy<<G4endl;
//    G4cout<<step->GetTrack()->GetMomentumDirection()<<G4endl;
    hc->Set_Neutron_Energy(Neutron_Energy);
    _phantomHC->insert(hc);
	}
  }

return true;
}
void phantomSD::EndOfEvent(G4HCofThisEvent*)
{
}
