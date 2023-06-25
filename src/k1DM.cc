#include "k1DM.hh"
#include "k1DC.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAString.hh"

k1DM::k1DM(k1DC* dc):G4UImessenger(),
	_DC(dc),
	_UIdir(0),
	_UIbodydir(0),
	_UImoderator(0),
	_UIreflector(0),
	_UIDAUcmdModeratorThickness(0),
	_UIfilter(0),
	_UIScmdModeratorMaterial(0),
	_UIScmdReflectorMaterial(0),
	_UIScmdFilterMaterial(0),
	_UIDAUcmdFilterThickness(0)
{
	//define directories
	_UIdir = new G4UIdirectory("/pf/");
	_UIbodydir= new G4UIdirectory("/pf/body/");
	_UImoderator= new G4UIdirectory("/pf/moderator/");
	_UIfilter = new G4UIdirectory("/pf/filter/");
	_UIcollimatordir = new G4UIdirectory("/pf/collimator/");

	//define UIcmds
	_UIDAUcmdModeratorThickness = new G4UIcmdWithADoubleAndUnit("/pf/moderator/thickness",this);
	_UIDAUcmdModeratorThickness->SetParameterName("MThick",false);
        _UIDAUcmdModeratorThickness->SetRange("MThick>0");
	_UIDAUcmdModeratorThickness->SetUnitCategory("Length");
	_UIScmdModeratorMaterial = new G4UIcmdWithAString("/pf/moderator/material",this);


	_UIDAUcmdCollimatorLength = new G4UIcmdWithADoubleAndUnit("/pf/collimator/length",this);
	_UIDAUcmdCollimatorLength->SetParameterName("MThick",false);
        _UIDAUcmdCollimatorLength->SetRange("MThick>0");
	_UIDAUcmdCollimatorLength->SetUnitCategory("Length");

	_UIDAUcmdCollimatorDiameter = new G4UIcmdWithADoubleAndUnit("/pf/collimator/holediameter",this);
	_UIDAUcmdCollimatorDiameter->SetParameterName("MThick",false);
        _UIDAUcmdCollimatorDiameter->SetRange("MThick>0");
	_UIDAUcmdCollimatorDiameter->SetUnitCategory("Length");

	
	_UIDAUcmdCollimatorLiningThickness = new G4UIcmdWithADoubleAndUnit("/pf/collimator/layerthickness",this);
	_UIDAUcmdCollimatorLiningThickness->SetParameterName("MThick",false);
        _UIDAUcmdCollimatorLiningThickness->SetRange("MThick>0");
	_UIDAUcmdCollimatorLiningThickness->SetUnitCategory("Length");

	_UIreflector= new G4UIdirectory("/pf/reflector/");
	_UIDAUcmdReflectorThickness = new G4UIcmdWithADoubleAndUnit("/pf/reflector/thickness",this);
	_UIDAUcmdReflectorThickness->SetParameterName("RThick",false);
        _UIDAUcmdReflectorThickness->SetRange("RThick>0");
	_UIDAUcmdReflectorThickness->SetUnitCategory("Length");

	
	_UIScmdReflectorMaterial = new G4UIcmdWithAString("/pf/reflector/material",this);

	_UIDAUcmdFilterThickness = new G4UIcmdWithADoubleAndUnit("/pf/filter/thickness",this);
	_UIDAUcmdFilterThickness->SetParameterName("FThick",false);
        _UIDAUcmdFilterThickness->SetRange("FThick>0");
	_UIDAUcmdFilterThickness->SetUnitCategory("Length");	
	_UIScmdFilterMaterial = new G4UIcmdWithAString("/pf/filter/material",this);

	_UIScmdCollimatorMaterial = new G4UIcmdWithAString("/pf/collimator/material",this);
	_UIScmdCollimatorLiningMaterial = new G4UIcmdWithAString("/pf/collimator/layermaterial",this);
}

k1DM::~k1DM()
{
delete _UIdir;
delete _UIDAUcmdModeratorThickness;
delete _UIbodydir;
delete _UImoderator;
delete _UIreflector;
delete _UIScmdFilterMaterial;
delete _UIScmdReflectorMaterial;
delete _UIScmdModeratorMaterial;
delete _UIScmdCollimatorLiningMaterial; 
delete _UIScmdCollimatorMaterial; 
delete _UIDAUcmdCollimatorDiameter;
delete _UIDAUcmdCollimatorLiningThickness;
delete _UIDAUcmdCollimatorLength;
}

void k1DM::SetNewValue(G4UIcommand* _UIcmd,G4String newValue)
{
//invoce function in DC for making chaneg in Geo
if(_UIcmd == _UIDAUcmdModeratorThickness) {_DC -> SetModeratorThickness(_UIDAUcmdModeratorThickness->GetNewDoubleValue(newValue));}
if(_UIcmd == _UIDAUcmdReflectorThickness) {_DC -> SetReflectorThickness(_UIDAUcmdReflectorThickness->GetNewDoubleValue(newValue));}
if(_UIcmd == _UIDAUcmdFilterThickness) {_DC -> SetFilterThickness(_UIDAUcmdFilterThickness->GetNewDoubleValue(newValue));}
if(_UIcmd == _UIDAUcmdCollimatorDiameter) {_DC -> SetCollimatorHoleDiameter(_UIDAUcmdCollimatorDiameter->GetNewDoubleValue(newValue));}
if(_UIcmd == _UIDAUcmdCollimatorLiningThickness) {_DC->SetCollimatorLayerThickness(_UIDAUcmdCollimatorLiningThickness->GetNewDoubleValue(newValue));}
if(_UIcmd == _UIDAUcmdCollimatorLength) {_DC -> SetCollimatorLength(_UIDAUcmdCollimatorLength->GetNewDoubleValue(newValue));}
if(_UIcmd == _UIScmdFilterMaterial) {_DC -> SetFilterMaterial(newValue);}
if(_UIcmd == _UIScmdReflectorMaterial) {_DC -> SetReflectorMaterial(newValue);}
if(_UIcmd == _UIScmdModeratorMaterial) {_DC -> SetModeratorMaterial(newValue);}
if(_UIcmd == _UIScmdCollimatorMaterial) {_DC -> SetCollimatorMaterial(newValue);}
if(_UIcmd == _UIScmdCollimatorLiningMaterial) {_DC -> SetCollimatorLayerMaterial(newValue);}
}





