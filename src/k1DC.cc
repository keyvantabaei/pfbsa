
#include "k1DC.hh"
#include "k1DM.hh"
#include "G4SDManager.hh"
#include "k1Geometery.cc"
#include "phantomSD.hh"
#include "Detector.hh"
#include <math.h>
#include "G4ParticleTable.hh"
#include <G4MultiFunctionalDetector.hh>
#include <G4VPrimitiveScorer.hh>
#include <G4PSDoseDeposit.hh>
//#include "G4VPrimitiveScorer.hh"
//#include "G4MultiFunctinalDetector.hh"
//#include "G4PSFlatSurfaceCurrent.hh"
k1DC::k1DC():G4VUserDetectorConstruction(),_phantom_size(G4ThreeVector(0,0,0))
,_DM(nullptr),geo(nullptr)
{
geo = new Geometery;
_DM = new k1DM(this);
}
k1DC::~k1DC()
{
	delete _DM;

}

G4VPhysicalVolume* k1DC::Construct()
{   
    //world definition
//    Geometery geo;
    G4double world_size=4*m;
    Struct _world =geo->Box("world","vacuum",G4ThreeVector(world_size,world_size,world_size),G4ThreeVector(),0,2);
  
//    geo->Tr = 10*cm;
//
//    G4cout<<"new aaa :"<<geo.aaa<<G4endl;	
auto _obj_geo = geo->PFBody2(_world._logic);  
  _collimator_detector_after = _obj_geo._logic;
  _collimator_detector_befor = _obj_geo._logic2;
  

   return _world._physical;
}
void k1DC::ConstructSDandField()
{
phantomSD* _target = new phantomSD("k1/phantomSD","photon");
G4SDManager::GetSDMpointer()->AddNewDetector(_target); //peyda kardan tedad photon vorodi be target dar energy E
SetSensitiveDetector(_collimator_detector_befor,_target); 
//auto detector = new G4MultuFunctionalDetector("plane3");
//G4SDManager::GetSDPointer()->AddNewDetector(detector);
//G4VPrimoterScorer* p1= new G4PSFlatSurfaceCurrent(); 
//
  Detector* _Detector = new Detector("k1/Detector","electron");
  G4SDManager::GetSDMpointer()->AddNewDetector(_Detector); // sabt tedad electron ha (compton va photoelectron)
  SetSensitiveDetector(_collimator_detector_after,_Detector);
  
  G4MultiFunctionalDetector* _cylndrMFD_collimator = new G4MultiFunctionalDetector("phantom_collimator");
  G4MultiFunctionalDetector* _cylndrMFD_around = new G4MultiFunctionalDetector("phantom_around");
  G4SDManager::GetSDMpointer()->AddNewDetector(_cylndrMFD_collimator);
  G4SDManager::GetSDMpointer()->AddNewDetector(_cylndrMFD_around);
  G4VPrimitiveScorer* _phantom_collimator = new G4PSDoseDeposit("collimator_phantom");
  G4VPrimitiveScorer* _phantom_around= new G4PSDoseDeposit("around_phantom");
  _cylndrMFD_collimator->RegisterPrimitive(_phantom_collimator);
  _cylndrMFD_around->RegisterPrimitive(_phantom_around);
  SetSensitiveDetector("phantomcollimatorL",_cylndrMFD_collimator);
  SetSensitiveDetector("phantomaroundL",_cylndrMFD_around);
  
}
void k1DC::SetModeratorThickness(G4double T)
{
	geo->Tm = T;
}
void k1DC::SetReflectorThickness(G4double T)
{
	geo->Tr = T;
}
void k1DC::SetFilterThickness(G4double T)
{
	geo->filter_thickness = T;
}
void k1DC::SetModeratorMaterial(G4String str)
{
	geo->MModeratorSTR = str;
}
void k1DC::SetReflectorMaterial(G4String str)
{
	geo->MReflectorSTR = str;
}
void k1DC::SetFilterMaterial(G4String str)
{
	geo->MFilterSTR = str;
}
void k1DC::SetCollimatorMaterial(G4String str)
{
	geo->MCollimatorSTR = str;
}
void k1DC::SetCollimatorLayerMaterial(G4String str)
{
	geo->MCollimatorLayerSTR = str;
}
void k1DC::SetCollimatorLayerThickness(G4double T)
{	geo->divergent_coll_layer_thickness = T;
}
void k1DC::SetCollimatorLength(G4double T)
{

	geo->divergent_coll_length = T;
}
void k1DC::SetCollimatorHoleDiameter(G4double T)
{
	geo->divergent_coll_radii=T/2;
}

