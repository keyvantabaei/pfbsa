#ifndef DetectorHit_h
#define DetectorHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "tls.hh"

class DetectorHit : public G4VHit
{
public:
//Construct and De-Construct Methods
DetectorHit();
virtual ~DetectorHit();
DetectorHit(const DetectorHit&);

//Virtual Method
virtual void Print();
virtual void Draw();

//operators
const DetectorHit& operator=(const DetectorHit&);
G4bool operator==(const DetectorHit&) const;
inline void* operator new (size_t);
inline void operator delete(void*);

void Set_Neutron_Energy(G4double e){neutron_energy=e;}
G4double Get_Neutron_Energy(){return neutron_energy;}




private:
G4double neutron_energy;


};

typedef G4THitsCollection<DetectorHit> detectorHC;
extern G4ThreadLocal G4Allocator<DetectorHit>* DetectorAllocator;
inline void* DetectorHit::operator new (size_t)
{
if(!DetectorAllocator)
DetectorAllocator = new G4Allocator<DetectorHit>;
return (void*)DetectorAllocator->MallocSingle();
}

inline void DetectorHit::operator delete(void *hit)
{
    DetectorAllocator->FreeSingle((DetectorHit*) hit);
}
#endif
