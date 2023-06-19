#ifndef k1AI_h
#define k1AI_h 1

#include "G4VUserActionInitialization.hh"


class k1AI : public G4VUserActionInitialization
{
  public:
    k1AI();
    virtual ~k1AI();

    virtual void BuildForMaster() const;
    virtual void Build() const;
};


#endif