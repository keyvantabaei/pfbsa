#include "G4LogicalVolume.hh"
#include <cmath>
#include "G4Cons.hh"
#include "G4SystemOfUnits.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Sphere.hh"
#include "G4VPhysicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4RotationMatrix.hh"
#include "G4PVParameterised.hh"
#include "G4PVParameterised.hh"
#include "G4SubtractionSolid.hh"
#include "G4Trd.hh"
#include "G4Trap.hh"
struct greaterSmaller { 
    G4VPhysicalVolume* _physical; 
    G4LogicalVolume* _logic;
    G4LogicalVolume* _logic2;
    G4VSolid* _SOLID;
}; 
typedef struct greaterSmaller Struct; 
class Geometery 
{
public:
//Dimentions
G4double lh=41.2*cm; // hole cylander lenght
G4double rh=5*cm; // hole small cylander radii
G4double L=50*cm; //main cylander lenght
G4double R=25*cm; // main cylander radii
G4double r=rh; // small cylander radii
G4double l=7.5*cm; // small cylander lenght
G4double bT=2*cm; //body thickness (2 cm)
G4double Tm=2*cm;//moderator thickness
G4double Tr=2*cm;//reflector tickness
G4double anode_radii=5/2*cm; // anode dimeter/2
G4double anode_lenght = 28.3*cm; //anode lengnht
G4double insulator_lenght = 14*cm;
G4double iT=7.5*mm; //insulator thickness
G4double cone_collimator_lenght=10*cm; //cone collimator lenght
G4double cone_collimator_hole_radii=2*cm; //cone collimator hole radius
G4double cathode_radii_t=0.5*cm; //cathode bar radii
G4double cathode_lenght=38*cm; //cathode lenght
G4double cathode_radii=9.8*cm; //cathode radii
G4double filter_thickness=1*cm;
G4int cathode_No=12;
G4double detector_r = 5*cm;
G4double detector_t = 1*cm;
G4double detector_befor_t = 0.1*mm;
G4double wallshieldT  = 5*cm; //head shield thickness
G4double wall_length = 3*m;
G4double phantom_diameter = 30*cm;
G4double divergent_coll_length = 20*cm; // divergent collimator length
G4double divergent_coll_radii = 3*cm; // divergent collimator diameter
G4double divergent_coll_layer_thickness = 1*cm; //collimator layer thickness
G4double coll_cover_thickness = 2*cm; //divergence collimator thickness

//Material Name
//defualt values
G4String MReflectorSTR=  "pb";
G4String MModeratorSTR=  "polyE";
G4String MFilterSTR=  "Bi";
G4String MCollimatorLayerSTR=  "polyE";
G4String MCollimatorSTR=  "polyE";


Struct Box(G4String name,G4String mat_name,G4ThreeVector size,G4ThreeVector pos)
{
G4RotationMatrix* rotm  =new G4RotationMatrix();
rotm->rotateY(-45*deg);
G4RotationMatrix* rotm_det  =new G4RotationMatrix();
rotm_det->rotateY(-90*deg); 
// rotm.rotateZ(phi);
Struct s;
// world box
s._SOLID = new G4Box(name+"_SOLID",size.x()/2,size.y()/2,size.z()/2);
// world logical
s._logic= new G4LogicalVolume(s._SOLID,create_material(mat_name),name+"_LOGIC");
// world physical
s._physical =new G4PVPlacement(0,G4ThreeVector(),s._logic,name+"_PHYSI",0,false,0,true); 
return s;
}

G4Material* create_material(G4String name)
{
    if(name=="steel")
    {
    G4Element* eCr=new G4Element("cripton","Cr",36,86*g/mole);
    G4Element* eFe=new G4Element("iron","Fe",26,54*g/mole);
     G4Material* _steel = new G4Material("Steel",1*g/cm3,2);
     _steel->AddElement(eCr,17);
     _steel->AddElement(eFe,83);
     return _steel;
    }
    else if(name=="car")
    {
    G4Element* eFe=new G4Element("iron","Fe",6,12*g/mole);
     G4Material* _steel = new G4Material("Steel",2*g/cm3,1);
     _steel->AddElement(eFe,1);
     return _steel;
    }   
     else if(name=="vacuum")
    {
     G4NistManager* nist = G4NistManager::Instance();
     G4Material* _world_mat = nist->FindOrBuildMaterial("G4_Galactic");
     return _world_mat;
    }
     else if(name=="cu")
    {
     G4NistManager* nist = G4NistManager::Instance();
     G4Material* _world_mat = nist->FindOrBuildMaterial("G4_Cu");
     return _world_mat;
    }
    else if(name=="pb")
    {
     G4NistManager* nist = G4NistManager::Instance();
     G4Material* _world_mat = nist->FindOrBuildMaterial("G4_Pb");
     return _world_mat;
    }
    else if(name=="Al")
    {
     G4NistManager* nist = G4NistManager::Instance();
     G4Material* _world_mat = nist->FindOrBuildMaterial("G4_Al");
     return _world_mat;
    }
    else if(name=="Bi")
    {
     G4NistManager* nist = G4NistManager::Instance();
     G4Material* _world_mat = nist->FindOrBuildMaterial("G4_Bi");
     return _world_mat;
    }
    else if(name=="polyE")
    {
     G4NistManager* nist = G4NistManager::Instance();
     G4Material* _world_mat = nist->FindOrBuildMaterial("G4_POLYETHYLENE");
     return _world_mat;
    }
    else if(name=="fe")
    {
     G4NistManager* nist = G4NistManager::Instance();
     G4Material* _world_mat = nist->FindOrBuildMaterial("G4_Fe");
     return _world_mat;
    }
     else if(name=="c")
    {
     G4NistManager* nist = G4NistManager::Instance();
     G4Material* _world_mat = nist->FindOrBuildMaterial("G4_C");
     return _world_mat;
    }
     else if(name=="b")
    {
     G4NistManager* nist = G4NistManager::Instance();
     G4Material* _world_mat = nist->FindOrBuildMaterial("G4_B");
     return _world_mat;
    }
     else if(name=="water")
    {
     G4NistManager* nist = G4NistManager::Instance();
     G4Material* _world_mat = nist->FindOrBuildMaterial("G4_WATER");
     return _world_mat;
    }
     else if(name=="pyrex")
    {
     G4NistManager* nist = G4NistManager::Instance();
     G4Material* _world_mat = nist->FindOrBuildMaterial("G4_Pyrex_Glass");
     return _world_mat;
    }
    else if(name=="polyE_borated")
    {
 G4Element* H=new G4Element("Hyd","H",1,1*g/mole);
   G4Element* C=new G4Element("Carbon","C",6,12*g/mole);
   G4Element* B=new G4Element("Boron","B",5,10*g/mole);
   G4Material* _boratedHDPE = new G4Material("polyethilene",1.03*g/cm3,3);
      _boratedHDPE ->AddElement(H,100);
     _boratedHDPE ->AddElement(C,50);
     _boratedHDPE ->AddElement(B,34);
     return _boratedHDPE;
    }
}

Struct PFBody2(G4LogicalVolume* mother_logic)
{
//Materials
G4Material* Mdetector=create_material("vacuum");
G4Material* Mbody=create_material("steel");
G4Material* Mmoderator=create_material(MModeratorSTR);
G4Material* Mreflector=create_material(MReflectorSTR);
G4Material* Minsulator=create_material("pyrex");
G4Material* Mcathode=create_material("cu");
G4Material* Manode=create_material("cu");
G4Material* Mcollimator=create_material(MCollimatorSTR);
G4Material* Mcollimator_layer=create_material(MCollimatorLayerSTR);
//G4Material* Mgas=create_material("steel");
G4Material* Mfilter=create_material(MFilterSTR);
G4Material* Mwall=create_material("polyE");
G4Material* Mphantom=create_material("water");

Struct s;
//Rotation Matrixs
G4RotationMatrix* myRotation5 = new G4RotationMatrix();
myRotation5->rotateY(90*deg); //body
G4RotationMatrix* myRotation0 = new G4RotationMatrix();
myRotation0->rotateY(90*deg); //body
G4RotationMatrix* myRotation2 = new G4RotationMatrix();
G4RotationMatrix* myRotation4 = new G4RotationMatrix();
myRotation2->rotateX(180*deg); //small cylander
myRotation4->rotateY(90*deg);  //small cylander
myRotation0->rotateX(90*deg);  //all other solids

// ROOM	
G4VSolid* _outer_box = new G4Box("outerS",wall_length/2,wall_length/2,wall_length/2);
G4VSolid* _inner_box = new G4Box("innerS",wall_length/2 - wallshieldT,wall_length/2 -wallshieldT,wall_length/2 -wallshieldT);
G4SubtractionSolid* _wallS = new G4SubtractionSolid("wallS",_outer_box,_inner_box,new G4RotationMatrix(),G4ThreeVector());
G4LogicalVolume* _wallL = new G4LogicalVolume(_wallS,Mwall,"wallL");
new G4PVPlacement(new G4RotationMatrix(),G4ThreeVector(),_wallL,"wallP",mother_logic,false,0,true);

// human phantom
G4VSolid* _phantomS = new G4Tubs("phantomS",0,phantom_diameter/2,1.75/2*m,0,360*deg);
G4LogicalVolume* _phantomcollimatorL = new G4LogicalVolume(_phantomS,Mphantom,"phantomcollimatorL");
G4LogicalVolume* _phantomaroundL = new G4LogicalVolume(_phantomS,Mphantom,"phantomaroundL");
new G4PVPlacement(new G4RotationMatrix(),G4ThreeVector(0,wall_length/2+phantom_diameter,0),_phantomcollimatorL,"phantomcollimatorP",mother_logic,false,0,true);
new G4PVPlacement(new G4RotationMatrix(),G4ThreeVector(wall_length/2+phantom_diameter,0,0),_phantomaroundL,"phantomaroundP",mother_logic,false,0,true);

// small cylanders around the body
G4VSolid* hole_s=new G4Tubs("hole_S",0,rh,lh/2,0,360*deg);//4 hole in body
G4VSolid* sc_s=new G4Tubs("sc_S",r-bT,r,l/2,0,360*deg);//small cylander around body
G4LogicalVolume* sc_l=new G4LogicalVolume(sc_s,Mbody,"sc_l"); //small cylander
new G4PVPlacement(myRotation4,G4ThreeVector(R+l/2,0,0),sc_l,"Bsc1_p",mother_logic,false,0,true); //small cylander
new G4PVPlacement(myRotation4,G4ThreeVector(-R-l/2,0,0),sc_l,"Bsc2_p",mother_logic,false,0,true); //
new G4PVPlacement(myRotation2,G4ThreeVector(0,0,R+l/2),sc_l,"Bsc3_p",mother_logic,false,0,true); //
new G4PVPlacement(myRotation2,G4ThreeVector(0,0,-R-l/2),sc_l,"Bsc4_p",mother_logic,false,0,true); //
new G4PVPlacement(myRotation0,G4ThreeVector(0,L/2+l/2,0),sc_l,"headsc_p",mother_logic,false,0,true); //small cylander head small cylander top of the anode


//body
G4VSolid* head_s= new G4Tubs("head",r,R-bT,bT/2,0,360*deg); //head
G4VSolid* mc_s=new  G4Tubs("mc_S",R-bT,R,L/2,0,360*deg);//main cylander of body
G4LogicalVolume* head_l=new G4LogicalVolume(head_s,Mbody,"head_l"); //head
G4LogicalVolume* body_l= new G4LogicalVolume(GetBodyShape(mc_s,hole_s,myRotation0,myRotation5,R),Mbody,"body_l"); //body
new G4PVPlacement(myRotation0,G4ThreeVector(0,L/2-bT/2,0),head_l,"head_p",mother_logic,false,0,true); //head
s._physical =new G4PVPlacement(myRotation0,G4ThreeVector(),body_l,"body_p",mother_logic,false,0,true); //body


// cathode base and electrodes
G4VSolid* cathode_s=new G4Tubs("cathode_s",0,cathode_radii_t,cathode_lenght/2,0,360*deg); //cathode
G4VSolid* cathode_base_s=new G4Tubs("cathode_base_s",anode_radii+iT,R-bT,bT/2,0,360*deg); //cathode base
G4VSolid* cathode_up_s=new G4Tubs("cathode_up_s",anode_radii+iT,(R-bT)/3,bT/2,0,360*deg); //cathode up
G4LogicalVolume* cathode_l=new G4LogicalVolume(cathode_s,Mcathode,"cathode_l"); // cathode
G4LogicalVolume* cathode_up_l=new G4LogicalVolume(cathode_up_s,Mcathode,"cathode_up_l"); //cathode_up
G4LogicalVolume* cathode_base_l=new G4LogicalVolume(cathode_base_s,Mcathode,"cathode_base_l"); //cathode_base
new G4PVPlacement(myRotation0,G4ThreeVector(0,-L/2+bT/2,0),cathode_base_l,"cathode_base_p",mother_logic,false,0,true); // cathode base
new G4PVPlacement(myRotation0,G4ThreeVector(0,-L/2+bT+bT/2,0),cathode_up_l,"cathode_up_p",mother_logic,false,0,true); //cathode up
G4double x;//calculate position of cathode bars
G4double y;
G4int t=360/cathode_No;
G4double theta=0;
for(G4int i=1;i<=cathode_No;i++)
{
theta=i*t;
x=cathode_radii*cos((theta/180)*M_PI);
y=cathode_radii*sin((theta/180)*M_PI);
new G4PVPlacement(myRotation0,G4ThreeVector(x,-L/2+bT+cathode_lenght/2,y),cathode_l,"cathode_p",mother_logic,false,0,true); //insulator
}

//anode and insulator
G4VSolid* insulator_s=new G4Tubs("insulator_s",anode_radii,anode_radii+iT,insulator_lenght/2,0,360*deg); //insulator
G4VSolid* anode_s=new G4Tubs("anode_s",0,anode_radii,anode_lenght/2,0,360*deg); //anode
G4LogicalVolume* insulator_l=new G4LogicalVolume(insulator_s,Minsulator,"insulator_l"); //insulator
G4LogicalVolume* anode_l=new G4LogicalVolume(anode_s,Manode,"anode_l"); //anode
new G4PVPlacement(myRotation0,G4ThreeVector(0,-L/2+bT/2+anode_lenght/2,0),anode_l,"anode_p",mother_logic,false,0,true); //anode
new G4PVPlacement(myRotation0,G4ThreeVector(0,-L/2+bT/2+insulator_lenght/2,0),insulator_l,"isulator_p",mother_logic,false,0,true); //insulator

//moderator
G4VSolid* moderator2_s = new G4Tubs("moderator_s",0,rh,Tm/2,0,360*deg); // top of the anode
G4VSolid* moderator_s = new G4Tubs("moderator_r",R,R+Tm,L/2,0,360*deg); //moderator
G4VSolid* moderator_head_s = new G4Tubs("moderator_head_s",r,R+Tr+Tm,Tm/2,0,360*deg); //moderator head
G4VSolid* moderator_base_s = new G4Tubs("moderator_base_s",0,R+Tm+Tr,Tm/2,0,360*deg); //modderator base
G4LogicalVolume* moderator2_l=new G4LogicalVolume(moderator2_s,Mmoderator,"moderator_l"); //moderator top of the anode
G4LogicalVolume* moderator_l=new G4LogicalVolume(GetBodyShape(moderator_s,hole_s,myRotation0,myRotation5,R+Tm),Mmoderator,"moderator_l"); //moderator
G4LogicalVolume* moderator_head_l=new G4LogicalVolume(moderator_head_s,Mmoderator,"moderator_head_l"); //moderator head
G4LogicalVolume* moderator_base_l=new G4LogicalVolume(moderator_base_s,Mmoderator,"moderator_head_l"); //moderator base
new G4PVPlacement(myRotation0,G4ThreeVector(),moderator_l,"moderator_p",mother_logic,false,0,true); //moderator
new G4PVPlacement(myRotation0,G4ThreeVector(0,L/2+Tm/2,0),moderator_head_l,"moderator_head_p",mother_logic,false,0,true); //moderator head
new G4PVPlacement(myRotation0,G4ThreeVector(0,-L/2-Tm/2,0),moderator_base_l,"moderator_base_p",mother_logic,false,0,true); //moderator base
new G4PVPlacement(myRotation0,G4ThreeVector(0,L/2+l+Tm/2,0),moderator2_l,"moderator2_phead",mother_logic,false,0,true); //moderator top of the anode
new G4PVPlacement(myRotation5,G4ThreeVector(L/2+l+Tm/2,0,0),moderator2_l,"moderator2_p2",mother_logic,false,0,true); //moderator around the body 
new G4PVPlacement(myRotation5,G4ThreeVector(-L/2-l-Tm/2,0,0),moderator2_l,"moderator2_p3",mother_logic,false,0,true); //moderator around the body
new G4PVPlacement(myRotation2,G4ThreeVector(0,0,-L/2-l-Tm/2),moderator2_l,"moderator2_p4",mother_logic,false,0,true); //moderator around the body
new G4PVPlacement(myRotation2,G4ThreeVector(0,0,L/2+l+Tm/2),moderator2_l,"moderator2_p5",mother_logic,false,0,true); //moderator around the body

//reflector
G4VSolid* reflector2_s = new G4Tubs("reflector_s",0,rh,Tr/2,0,360*deg); // top of the anode
G4VSolid* reflector_s = new G4Tubs("reflector_s",R+Tm,R+Tm+Tr,L/2,0,360*deg); //reflector
G4VSolid* reflector_head_s = new G4Tubs("reflector_head_s",r,R+Tm+Tr,Tr/2,0,360*deg); //reflector head
G4VSolid* reflector_base_s = new G4Tubs("reflector_base_s",0,R+Tm+Tr,Tr/2,0,360*deg); //reflector base
G4LogicalVolume* reflector2_l=new G4LogicalVolume(reflector2_s,Mreflector,"reflector_l"); // reflectortop of the anode 
G4LogicalVolume* reflector_l=new G4LogicalVolume(GetBodyShape(reflector_s,hole_s,myRotation0,myRotation5,R+Tm+Tr),Mreflector,"reflector_l"); //reflector
G4LogicalVolume* reflector_head_l=new G4LogicalVolume(reflector_head_s,Mreflector,"reflector_head_l"); //reflector head
G4LogicalVolume* reflector_base_l=new G4LogicalVolume(reflector_base_s,Mreflector,"reflector_head_l"); //reflector base
new G4PVPlacement(myRotation0,G4ThreeVector(),reflector_l,"reflector_p",mother_logic,false,0,true); //reflector
new G4PVPlacement(myRotation0,G4ThreeVector(0,L/2+Tm+Tr/2,0),reflector_head_l,"reflector_head_p",mother_logic,false,0,true); //reflector head
new G4PVPlacement(myRotation0,G4ThreeVector(0,-L/2-Tr/2-Tm,0),reflector_base_l,"reflector_base_p",mother_logic,false,0,true); //reflector base
//new G4PVPlacement(myRotation0,G4ThreeVector(0,L/2+l+Tm+Tr/2,0),reflector2_l,"reflector2_head_p",mother_logic,false,0,true); //reflector top of the body
new G4PVPlacement(myRotation5,G4ThreeVector(L/2+l+Tm+Tr/2,0,0),reflector2_l,"reflector2_p1",mother_logic,false,0,true); //reflector around the body
new G4PVPlacement(myRotation5,G4ThreeVector(-L/2-l-Tm-Tr/2,0,0),reflector2_l,"reflector2_p2",mother_logic,false,0,true); //reflecto around the body
new G4PVPlacement(myRotation2,G4ThreeVector(0,0,-L/2-l-Tm-Tr/2),reflector2_l,"reflector2_p3",mother_logic,false,0,true); //reflector around the body
new G4PVPlacement(myRotation2,G4ThreeVector(0,0,L/2+l+Tm+Tr/2),reflector2_l,"reflector2_p4",mother_logic,false,0,true); //reflector around the body


// filter
G4VSolid* filter_s=new G4Tubs("filter_S",0,r,filter_thickness/2,0,360*deg);// filter solid
G4LogicalVolume* filter_l=new G4LogicalVolume(filter_s,Mfilter,"filter_l"); // filter logic
new G4PVPlacement(myRotation0,G4ThreeVector(0,L/2+filter_thickness/2+l/*+Tr*/+Tm,0),filter_l,"filter_p",mother_logic,false,0,true); //filter physical


// collimator
G4VSolid* collimator_s=new G4Cons("collimator_s",r-0.5*cm,r,cone_collimator_hole_radii,cone_collimator_hole_radii+0.5*cm,cone_collimator_lenght/2,0,360*deg); //collimator
G4LogicalVolume* collimator_l=new G4LogicalVolume(collimator_s,Mcollimator,"collimator_l"); // collimator
//new G4PVPlacement(myRotation0,G4ThreeVector(0,L/2+l+cone_collimator_lenght/2+filter_thickness+Tr+Tm,0),collimator_l,"collimator_p",mother_logic,false,0,true); //collimator

// detector
G4VSolid* detector_s_after_coll=new  G4Tubs("mc_S",0,detector_r,detector_t/2,0,360*deg);// detector solid
//G4VSolid* detector_s=new G4Sphere("detector_s",0.95*m,1*m,0,360*deg,0,180*deg);
s._logic=new G4LogicalVolume(detector_s_after_coll,Mdetector,"detector_l"); //insulator
new G4PVPlacement(myRotation0,G4ThreeVector(0,L/2+l+divergent_coll_length+filter_thickness/*+Tr*/+Tm+detector_t/2+detector_befor_t,0),s._logic,"detector_p",mother_logic,false,0,true); // detector after

G4VSolid* detector_s_befor_coll=new  G4Tubs("mc_S",0,detector_r,detector_befor_t/2,0,360*deg);// detector solid
//G4VSolid* detector_s=new G4Sphere("detector_s",0.95*m,1*m,0,360*deg,0,180*deg);
s._logic2=new G4LogicalVolume(detector_s_befor_coll,Mdetector,"detector_l"); //insulator
new G4PVPlacement(myRotation0,G4ThreeVector(0,L/2+l+filter_thickness/*+Tr*/+Tm+detector_befor_t/2,0),s._logic2,"detector_p_befor",mother_logic,false,0,true); // detector befor


//divergent collimator
//G4VSolid* _tubeS = new G4Tubs("divergentcosllS",0,r,divergent_coll_length/2,0,360*deg);
G4VSolid* _tubeS = new G4Box("",r,r,divergent_coll_length/2);
G4VSolid* _coneS=new G4Cons("divergentcollS",0,divergent_coll_radii+divergent_coll_layer_thickness,0,r,divergent_coll_length/2+1*mm,0,360*deg); //collimator
G4SubtractionSolid* _collimatorS = new G4SubtractionSolid("collimatorS",_tubeS,_coneS,new G4RotationMatrix(),G4ThreeVector());
G4LogicalVolume* _collimatorL = new G4LogicalVolume(_collimatorS,Mcollimator,"collimatorL");

G4VSolid* _coneS_layer=new G4Cons("divergentcollS_layer",divergent_coll_radii,divergent_coll_layer_thickness-.3*mm,r-divergent_coll_layer_thickness,r-.3*mm,divergent_coll_length/2,0,360*deg); // collimator layer
G4LogicalVolume* _collimator_layer_L = new G4LogicalVolume(_coneS_layer,Mcollimator_layer,"collimato_layer_L");

new G4PVPlacement(new G4RotationMatrix(0,-90*deg,0),G4ThreeVector(0,detector_befor_t+L/2+l+divergent_coll_length/2+filter_thickness/*+Tr*/+Tm,0),_collimatorL,"collimatorP",mother_logic,false,0,true);
	
new G4PVPlacement(new G4RotationMatrix(0,-90*deg,0),G4ThreeVector(0,detector_befor_t+L/2+l+divergent_coll_length/2+filter_thickness/*+Tr*/+Tm,0),_collimator_layer_L,"collimator_layer_P",mother_logic,false,0,true);

G4VSolid* _outer_box_coll = new G4Box("outerS_coll",r+coll_cover_thickness,r+coll_cover_thickness,divergent_coll_length/2);
G4VSolid* _inner_box_coll = new G4Box("innerS_coll",r,r,divergent_coll_length/2+1*mm);
G4SubtractionSolid* _wallS_coll = new G4SubtractionSolid("wallS_coll",_outer_box_coll,_inner_box_coll,new G4RotationMatrix(),G4ThreeVector());
G4LogicalVolume* _wallL_coll = new G4LogicalVolume(_wallS_coll,Mwall,"wallL_coll");
new G4PVPlacement(new G4RotationMatrix(0,-90*deg,0),G4ThreeVector(0,detector_befor_t+L/2+l+divergent_coll_length/2+filter_thickness/*+Tr*/+Tm,0),_wallL_coll,"collimator_cover_p",mother_logic,false,0,true);



return s;
}

G4SubtractionSolid* GetBodyShape(G4VSolid* mc_s,G4VSolid* hole_s,G4RotationMatrix* myRotation0,G4RotationMatrix* myRotation5, G4double R )
{
G4SubtractionSolid *hC1= new G4SubtractionSolid("HC1",mc_s,hole_s,myRotation5,G4ThreeVector(R+1*cm,0,0)); //body
G4SubtractionSolid *hC2= new G4SubtractionSolid("HC2",hC1,hole_s,myRotation0,G4ThreeVector(0,R+1*cm,0));
G4SubtractionSolid *hC3= new G4SubtractionSolid("HC3",hC2,hole_s,myRotation5,G4ThreeVector(-R-1*cm,0,0));
G4SubtractionSolid *hC4= new G4SubtractionSolid("HC4",hC3,hole_s,myRotation0,G4ThreeVector(0,-R-1*cm,0));
return hC4;
}


};
