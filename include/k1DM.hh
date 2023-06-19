#ifndef k1DM_h
#define k1DH_h 1

#include <G4UImessenger.hh>
#include <globals.hh>

class k1DC;
class G4UIcmdWithADoubleAndUnit;
class G4UIdirectory;
class G4UIcmdWithAString;

class k1DM : public G4UImessenger
{
public:
	k1DM(k1DC*);
	~k1DM();
	void SetNewValue(G4UIcommand*,G4String) override;

private:
	k1DC* _DC;
	G4UIdirectory* _UIdir;
	G4UIdirectory* _UIbodydir;
	G4UIdirectory* _UImoderator;
	G4UIdirectory* _UIreflector;
	G4UIdirectory* _UIfilter;
	G4UIdirectory* _UIcollimatordir;

	G4UIcmdWithADoubleAndUnit* _UIDAUcmdModeratorThickness;
	G4UIcmdWithADoubleAndUnit* _UIDAUcmdReflectorThickness;
	G4UIcmdWithADoubleAndUnit* _UIDAUcmdFilterThickness;

	G4UIcmdWithADoubleAndUnit* _UIDAUcmdCollimatorLength;
	G4UIcmdWithADoubleAndUnit* _UIDAUcmdCollimatorDiameter;
	G4UIcmdWithADoubleAndUnit* _UIDAUcmdCollimatorThickness;
	G4UIcmdWithADoubleAndUnit* _UIDAUcmdCollimatorLiningThickness;

	G4UIcmdWithAString* _UIScmdModeratorMaterial;
	G4UIcmdWithAString* _UIScmdReflectorMaterial;
	G4UIcmdWithAString* _UIScmdFilterMaterial;

	G4UIcmdWithAString* _UIScmdCollimatorMaterial;
	G4UIcmdWithAString* _UIScmdCollimatorLiningMaterial;

};
#endif
