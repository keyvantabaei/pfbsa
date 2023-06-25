#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4UnitsTable.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "k1EA.hh"
#include "k1RA.hh"
#include "HistoManager.hh"
#include "G4AnalysisManager.hh"
#include <G4THitsMap.hh>

k1EA::k1EA(k1RA* ra,HistoManager* histo)
 : G4UserEventAction(),_neutron_HCID(-1),_photon_HCID(-1),_histo(histo),_runAction(ra)
{

}


k1EA::~k1EA()
{

}

phantomHC*  k1EA::GetphantomHitsCollection(G4int hcID,const G4Event* event) const
{
  auto hitsCollection = static_cast<phantomHC*>(event->GetHCofThisEvent()->GetHC(hcID));
  if ( ! hitsCollection ) 
  {
    G4ExceptionDescription msg;
    msg << "Cannot access hitsCollection ID " << hcID; 
    G4Exception("B4cEventAction::GetHitsCollection()","MyCode0003", FatalException, msg);
  }         
  return hitsCollection;
}  

detectorHC*  k1EA::GetDetectorHitsCollection(G4int hcID,const G4Event* event) const
{
  auto hitsCollection = static_cast<detectorHC*>(event->GetHCofThisEvent()->GetHC(hcID));
  if ( ! hitsCollection ) 
  {
    G4ExceptionDescription msg;
    msg << "Cannot access hitsCollection ID " << hcID; 
    G4Exception("B4cEventAction::GetHitsCollection()","MyCode0003", FatalException, msg);
  }         
  return hitsCollection;
}  

void k1EA::BeginOfEventAction(const G4Event* event)
{
  G4int evtNb = event->GetEventID();
  if (evtNb%1000000 == 0 && evtNb/1000000 != 0 ) 
    G4cout << "\n---> Begin of event: " << evtNb/1000000 <<" M"<< G4endl;
}

void k1EA::EndOfEventAction(const G4Event* event)
{ 
//Get HC of this Event
G4HCofThisEvent* HC = event->GetHCofThisEvent();

//Get Collection ID of phantom Detector MultiFunctional Detector
G4int collimator_phantom_ID = G4SDManager::GetSDMpointer()->GetCollectionID("phantom_collimator/collimator_phantom");
G4int around_phantom_ID = G4SDManager::GetSDMpointer()->GetCollectionID("phantom_around/around_phantom");

// Get G4HitsMap
 auto collimator_phantom_HitsMap = (G4THitsMap<G4double>*)(HC->GetHC(collimator_phantom_ID));
 auto around_phantom_HitsMap = (G4THitsMap<G4double>*)(HC->GetHC(around_phantom_ID));
 
//Create Iterator
 std::map<G4int,G4double*>::iterator collimator_it;
 std::map<G4int,G4double*>::iterator around_it;

 // iterator throught Map and score deposited dose
 G4double collimator_phantom_dose =0,around_phantom_dose=0;
 for (collimator_it =collimator_phantom_HitsMap->GetMap()->begin() ;collimator_it!=collimator_phantom_HitsMap->GetMap()->end();++collimator_it )
 {
	collimator_phantom_dose += *(collimator_it->second);
 }
 for (around_it =around_phantom_HitsMap->GetMap()->begin() ;around_it!=around_phantom_HitsMap->GetMap()->end();++around_it )
 {
	around_phantom_dose += *(around_it->second);

 }
// add dose to RunAction Class
_runAction->Add_Collimator_Phantom_Dose(collimator_phantom_dose);
_runAction->Add_Around_Phantom_Dose(around_phantom_dose);
//Get hits collections IDs (only once)
if ( _neutron_HCID == -1 ) 
_neutron_HCID = G4SDManager::GetSDMpointer()->GetCollectionID("electron");
if ( _photon_HCID == -1 ) 
_photon_HCID = G4SDManager::GetSDMpointer()->GetCollectionID("photon");

// Get HCs object
auto _phantomHC = GetphantomHitsCollection(_photon_HCID, event);
auto _DetectorHC = GetDetectorHitsCollection(_neutron_HCID, event);

// HCs object lenght
auto phantomHC_lenght = _phantomHC->entries();
auto DetectorHC_lenght = _DetectorHC->entries();

// Fill Histograms by neutrons
auto analysisManager = G4AnalysisManager::Instance();
for(size_t i=0;i<phantomHC_lenght;i++)
{
  auto _hit = (*_phantomHC)[i];
  G4double neutron_energy_befor=_hit->Get_Neutron_Energy();
  analysisManager->FillH1(1, neutron_energy_befor);
}
for(size_t i=0;i<DetectorHC_lenght;i++)
{
  auto _hit = (*_DetectorHC)[i];
  G4double neutron_energy=_hit->Get_Neutron_Energy();
  analysisManager->FillH1(0, neutron_energy);
}



}  
