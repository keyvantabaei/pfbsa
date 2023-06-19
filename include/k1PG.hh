
#ifndef k1PG_h
#define k1PG_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4GeneralParticleSource.hh"

class G4GeneralParticleSource;
class G4Event;

class k1PG : public G4VUserPrimaryGeneratorAction
{
  public:
    k1PG();    
    virtual ~k1PG();

    // method from the base class
    virtual void GeneratePrimaries(G4Event*);         
    protected:
    G4GeneralParticleSource* gps;
  
};

#endif