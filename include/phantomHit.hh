#ifndef phantomHit_h
#define phantomHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "tls.hh"

class phantomHit : public G4VHit
{
public:
//Construct and De-Construct Methods
phantomHit();
virtual ~phantomHit();
phantomHit(const phantomHit&);

//Virtual Method
virtual void Print();
virtual void Draw();

//operators
const phantomHit& operator=(const phantomHit&);
G4bool operator==(const phantomHit&) const;
inline void* operator new (size_t);
inline void operator delete(void*);

void Set_Neutron_Energy(G4double e){neutron_energy=e;}
G4double Get_Neutron_Energy(){return neutron_energy;}




private:
G4double neutron_energy;

};

typedef G4THitsCollection<phantomHit> phantomHC;
extern G4ThreadLocal G4Allocator<phantomHit>* phantomAllocator;
inline void* phantomHit::operator new (size_t)
{
if(!phantomAllocator)
phantomAllocator = new G4Allocator<phantomHit>;
return (void*)phantomAllocator->MallocSingle();
}

inline void phantomHit::operator delete(void *hit)
{
    phantomAllocator->FreeSingle((phantomHit*) hit);
}
#endif
