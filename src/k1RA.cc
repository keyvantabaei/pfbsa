#include "k1RA.hh"
#include "k1DC.hh"
#include "HistoManager.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4AccumulableManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4Run.hh"
#include "G4AnalysisManager.hh"
k1RA::k1RA(HistoManager* histo): G4UserRunAction(),_histo(histo)
{
//Define Accumulators and Histograms
G4AccumulableManager* accumulable = G4AccumulableManager::Instance();
accumulable->RegisterAccumulable( collimator_phantom_dose);
accumulable->RegisterAccumulable(collimator_phantom_dose2);
accumulable->RegisterAccumulable(around_phantom_dose);
accumulable->RegisterAccumulable(around_phantom_dose2);  
auto analysisManager = G4AnalysisManager::Instance();
analysisManager->SetVerboseLevel(0);
analysisManager->SetNtupleMerging(true);
analysisManager->CreateH1("neutrons_after","neutron energy dist", 2450, 0., 2.45*MeV);
analysisManager->CreateH1("neutrons_before","neutron energy dist", 2450, 0., 2.45*MeV);
}
k1RA::~k1RA()
{ }


void k1RA::BeginOfRunAction(const G4Run* run)
{ 
G4cout << "### Run " << run->GetRunID() << " start." << G4endl;
// reset accumulables to their initial values
G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
accumulableManager->Reset();
auto analysisManager = G4AnalysisManager::Instance();
// Open an output file
G4String fileName = "pfBSA.root";
analysisManager->OpenFile(fileName);
//inform the runManager to save random number seed
G4RunManager::GetRunManager()->SetRandomNumberStore(false);
}

void k1RA::EndOfRunAction(const G4Run* run)
{
G4int NoEvt = run->GetNumberOfEvent();
if(NoEvt == 0)return;//do nothing if no particle is tracked
G4AccumulableManager* accumulable = G4AccumulableManager::Instance();
accumulable->Merge();//merge accumulators in MT mode
auto analysisManager = G4AnalysisManager::Instance();
analysisManager->Write();
analysisManager->CloseFile();
//Error calculation
G4double variance_collimator = collimator_phantom_dose2.GetValue() - collimator_phantom_dose.GetValue()*collimator_phantom_dose.GetValue()/NoEvt;
G4double variance_around = around_phantom_dose2.GetValue() - around_phantom_dose.GetValue()*around_phantom_dose.GetValue()/NoEvt;
variance_collimator = std::sqrt(variance_collimator);
variance_around = std::sqrt(variance_around);
if(IsMaster())
{
G4cout<< "Collimator Phantom Dose = "<<G4BestUnit(collimator_phantom_dose.GetValue(),"Dose")<<" +- "<<G4BestUnit(variance_collimator,"Dose")<<G4endl;
G4cout<< "Around Phantom Dose = "<<G4BestUnit(around_phantom_dose.GetValue(),"Dose")<<" +- "<<G4BestUnit(variance_around,"Dose")<<G4endl;
}
}
