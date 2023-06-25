#ifndef k1DC_h
#define k1DC_h 1

#include "G4VUserDetectorConstruction.hh"
#include "G4ThreeVector.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;
class k1DM;
class Geometery;
class k1DC  : public G4VUserDetectorConstruction
{
    public:
    k1DC();
    virtual ~k1DC();
virtual void ConstructSDandField();
virtual G4VPhysicalVolume* Construct();

//Define functions for making change by commands
void SetModeratorThickness(G4double);
void SetReflectorThickness(G4double);
void SetFilterThickness(G4double);
void SetReflectorMaterial(G4String);
void SetModeratorMaterial(G4String);
void SetFilterMaterial(G4String);

void SetCollimatorMaterial(G4String);
void SetCollimatorLayerMaterial(G4String);
void SetCollimatorLayerThickness(G4double);
void SetCollimatorLength(G4double);
void SetCollimatorHoleDiameter(G4double);
//End of defining functions
private:
//Define LV of Detector and obj of geo and messenger classes 
G4LogicalVolume* _collimator_detector_after;
G4LogicalVolume* _collimator_detector_befor;
G4LogicalVolume* _shielding_detector;
k1DM* _DM;
Geometery* geo;

};

#endif
