
#include "k1DC.hh"
#include "k1AI.hh"
//#include "PhysicsList.hh"
 #ifdef G4MULTITHREADED
 #include "G4MTRunManager.hh"
 #else
#include "G4RunManager.hh"
 #endif

#include "G4UImanager.hh"
//#include "QBBC.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "Randomize.hh"

//new line
#include "QGSP_BERT_HP.hh"
int main(int argc,char** argv)
{
  G4UIExecutive* ui = 0;
  if ( argc == 1 ) {
    ui = new G4UIExecutive(argc, argv);
  }

#ifdef G4MULTITHREADED
G4MTRunManager* runManager = new G4MTRunManager;
 #else
  G4RunManager* runManager = new G4RunManager;
 #endif
runManager->SetNumberOfThreads(12);
  runManager->SetUserInitialization(new k1DC());

  // Physics list
  // G4VModularPhysicsList* physicsList = new QBBC;
  G4VModularPhysicsList* physicsList = new QGSP_BERT_HP;
   physicsList->SetVerboseLevel(0);
  // runManager->SetUserInitialization(physicsList);
//  runManager->SetUserInitialization(new PhysicsList());
  runManager->SetUserInitialization(physicsList); 
    
  // User action initialization
  runManager->SetUserInitialization(new k1AI());

  // Initialize visualization
  //
  G4VisManager* visManager = new G4VisExecutive;
  // G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
  // G4VisManager* visManager = new G4VisExecutive("Quiet");
  visManager->Initialize();

  // Get the pointer to the User Interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  // Process macro or start UI session
  //
  if ( ! ui ) { 
    // batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  }
  else { 
    // interactive mode
    UImanager->ApplyCommand("/control/execute init_vis.mac");
    ui->SessionStart();
    delete ui;
       }
  delete visManager;
  delete runManager;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
