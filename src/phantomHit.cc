#include "phantomHit.hh"
#include "G4VHit.hh"
#include "G4ThreeVector.hh"
#include "G4Allocator.hh"
#include <iomanip>
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
G4ThreadLocal G4Allocator<phantomHit>* phantomAllocator=0;

phantomHit::phantomHit():G4VHit()
{
neutron_energy=-1;
}

phantomHit::~phantomHit(){}

phantomHit::phantomHit(const phantomHit& K1BH):G4VHit()
{
    
    neutron_energy=K1BH.neutron_energy;


}
const phantomHit& phantomHit::operator=(const phantomHit& K1BH)
{
    neutron_energy=K1BH.neutron_energy;


    return *this;
}

G4bool phantomHit::operator==(const phantomHit& K1BH) const
{
    return (this == &K1BH) ? true : false;
}

void phantomHit::Print()
{
}

void phantomHit::Draw()
{
}
