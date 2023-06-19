#include "DetectorHit.hh"
#include "G4VHit.hh"
#include "G4ThreeVector.hh"
#include "G4Allocator.hh"
#include <iomanip>
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
G4ThreadLocal G4Allocator<DetectorHit>* DetectorAllocator=0;

DetectorHit::DetectorHit():G4VHit()
{
neutron_energy=-1;

}

DetectorHit::~DetectorHit(){}

DetectorHit::DetectorHit(const DetectorHit& K1BH):G4VHit()
{
    neutron_energy=K1BH.neutron_energy;
}
const DetectorHit& DetectorHit::operator=(const DetectorHit& K1BH)
{
    neutron_energy=K1BH.neutron_energy;;
    return *this;
}

G4bool DetectorHit::operator==(const DetectorHit& K1BH) const
{
    return (this == &K1BH) ? true : false;
}

void DetectorHit::Print()
{
}

void DetectorHit::Draw()
{
}
