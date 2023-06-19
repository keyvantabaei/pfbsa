#include "k1PG.hh"

k1PG::k1PG()
: G4VUserPrimaryGeneratorAction(),gps(0)
{
    gps = new G4GeneralParticleSource();
}


k1PG::~k1PG()
{
        delete gps;
}


void k1PG::GeneratePrimaries(G4Event* anEvent)
{
    gps -> GeneratePrimaryVertex(anEvent);
}

