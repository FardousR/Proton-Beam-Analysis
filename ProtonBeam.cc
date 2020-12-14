

#include "G4UIExecutive.hh"
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"
#include "ActionInitialization.hh"
#include "DetectorConstruction.hh"
#include "G4UIQt.hh"
#include "G4SystemOfUnits.hh"
#include "G4UImanager.hh"
#include "QBBC.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "Randomize.hh"
#include "G4PhysListFactory.hh"
#include "G4StepLimiterPhysics.hh"

#include <getopt.h>

// #ifdef G4MULTITHREADED
// #include "G4MTRunManager.hh"
// #else
#include "G4RunManager.hh"
// #endif

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif


int main(int argc,char** argv)
{

    //Parse command line arguments

    DetectorConstruction* detector;
    //G4double   x=4.0; //unused and unobvious what it is
    G4double   beam_energy         = 150.0*MeV;
    G4double   beam_sigma_x        = 3.0*mm;
    G4double   beam_sigma_y        = 3.0*mm;
    G4double   beam_alpha_x        = 0.0;
    G4double   beam_alpha_y        = 0.0;
    G4double   beam_beta_x         = 0.82*m;
    G4double   beam_beta_y         = 0.82*m;
    G4int      num_particle        = 100;
    G4double   gun_z_position      = -1.0*mm;
    G4bool     collimator          = false;
    G4double   collimator_radius   = 3.0*mm;
    G4double   max_step_length     = 0.2*mm;
    G4bool     useGUI              = false;

  if(collimator)
    {
        gun_z_position = -800.00*mm;
    }
  else
   {
       gun_z_position = - 0.1*mm;
   }


   static struct option long_options[] = {
                                          {"energy",                    required_argument, NULL, 'e'   },
                                          {"alphax",                    required_argument, NULL, 'a'   },
                                          {"betax",                     required_argument, NULL, 'b'   },
                                          {"sizex",                     required_argument, NULL, 's'   },
                                          {"alphay",                    required_argument, NULL, 1000  },
                                          {"betay",                     required_argument, NULL, 1001  },
                                          {"sizey",                     required_argument, NULL, 1002  },
                                          {"number",                    required_argument, NULL, 'n'   },
                                          {"step",                      required_argument, NULL, 'l'   },
                                          {"gui",                       no_argument,       NULL, 'g'   },
                                          {"col",                       no_argument,       NULL, 'c'   },
                                          {"colrad",                    required_argument, NULL, 'r'   },
                                          {0,0,0,0}
   };

   int getopt_char;
   int getopt_idx;
   extern int optopt;

   while ( (getopt_char = getopt_long(argc,argv, ":e:a:b:l:n:s:r:gc", long_options, &getopt_idx)) != -1) {
     // Note: optstring starts with a ":" in order to give useful feedback if argument is missing.
     
       switch(getopt_char) {

       case 'g': //Use GUI
           useGUI = true;
           break;

       case 'c': //Collimator On/Off
           collimator = true;
           break;


       case 'e': //Beam Energy
           try
           {
             beam_energy = std::stod(std::string(optarg))*MeV;
           }
           catch (const std::invalid_argument& ia) {
               G4cout << "Invalid argument when reading beam energy" << G4endl
                      << "Got: '" << optarg << "'" << G4endl
                      << "Expected a floating point number! (exponential notation is accepted)" << G4endl;
               exit(1);
           }
           break;

       case 'a': //Beam Alpha(x)
           try {
               beam_alpha_x  = std::stod(std::string(optarg));
           }
           catch (const std::invalid_argument& ia) {
               G4cout << "Invalid argument when reading Alpha(x)" << G4endl
                      << "Got: '" << optarg << "'" << G4endl
                      << "Expected a floating point number! (exponential notation is accepted)" << G4endl;
               exit(1);
           }
           break;

       case 1000: //Beam Alpha(y)
           try {
               beam_alpha_y  = std::stod(std::string(optarg));
           }
           catch (const std::invalid_argument& ia) {
               G4cout << "Invalid argument when reading Alpha(y)" << G4endl
                      << "Got: '" << optarg << "'" << G4endl
                      << "Expected a floating point number! (exponential notation is accepted)" << G4endl;
               exit(1);
           }
           break;

       case 'b': //Beam Beta(x)
           try {
               beam_beta_x = std::stod(std::string(optarg))*m;
           }
           catch (const std::invalid_argument& ia) {
               G4cout << "Invalid argument when reading Beta(x)" << G4endl
                      << "Got: '" << optarg << "'" << G4endl
                      << "Expected a floating point number! (exponential notation is accepted)" << G4endl;
               exit(1);
           }
           break;

       case 1001: //Beam Beta(y)
           try {
               beam_beta_y = std::stod(std::string(optarg))*m;
           }
           catch (const std::invalid_argument& ia) {
               G4cout << "Invalid argument when reading Beta(y)" << G4endl
                      << "Got: '" << optarg << "'" << G4endl
                      << "Expected a floating point number! (exponential notation is accepted)" << G4endl;
               exit(1);
           }
           break;

       case 'n': //Number of Particle
           try {
               num_particle = std::stod(std::string(optarg));
           }
           catch (const std::invalid_argument& ia) {
               G4cout << "Invalid argument when reading number of particles" << G4endl
                      << "Got: '" << optarg << "'" << G4endl
                      << "Expected a integer number! (exponential notation is accepted)" << G4endl;
               exit(1);
           }
           break;

       case 's': //Beam Sigma(x)
           try {
               beam_sigma_x = std::stod(std::string(optarg))*mm;
           }
           catch (const std::invalid_argument& ia) {
               G4cout << "Invalid argument when reading beam sigma(x)" << G4endl
                      << "Got: '" << optarg << "'" << G4endl
                      << "Expected a integer number! (exponential notation is accepted)" << G4endl;
               exit(1);
           }
           break;

       case 1002: //Beam Sigma(y)
           try {
               beam_sigma_y = std::stod(std::string(optarg))*mm;
           }
           catch (const std::invalid_argument& ia) {
               G4cout << "Invalid argument when reading beam sigma(y)" << G4endl
                      << "Got: '" << optarg << "'" << G4endl
                      << "Expected a integer number! (exponential notation is accepted)" << G4endl;
               exit(1);
           }
           break;


       case 'l': // Maximum step length
           try {
               max_step_length = std::stod(std::string(optarg))*mm;
           }
           catch (const std::invalid_argument& ia) {
               G4cout << "Invalid argument when reading beam step limit" << G4endl
                      << "Got: '" << optarg << "'" << G4endl
                      << "Expected a floating point number! (exponential notation is accepted)" << G4endl;
               exit(1);
           }
           break;

       case 'r': // Collimator radius
           try {
               collimator_radius = std::stod(std::string(optarg))*mm;
           }
           catch (const std::invalid_argument& ia) {
               G4cout << "Invalid argument when reading collimator radius" << G4endl
                      << "Got: '" << optarg << "'" << G4endl
                      << "Expected a floating point number! (exponential notation is accepted)" << G4endl;
               exit(1);
           }
           break;

     //Error handling:
       case ':': // Missing argument
	 G4cout << "One of the given options expected an argument, but it was missing." << G4endl;
	 if ( isalpha(optopt) ) {
	   G4cout << "The option was: '" << char(optopt) << "'" << G4endl;
	 }
	 exit(1);
	 break;

       case '?': // Unknown argument
	 G4cout << "One of the given optios are unknown to getopt" << G4endl;
	 if ( isalpha(optopt) ) {
	   G4cout << "The option was: '" << char(optopt) << "'" << G4endl;
	 }
	 exit(1);
	 break;
	 
       default: // Something bad happened -- detect it now, otherwise things can go wrong later, and it will be hard to debug.
	 G4cout << "Internal error: getopt_long recognized the flag '" << char(getopt_char) << "' ("<< getopt_char<<"), but the switch/case did not." << G4endl;
	 exit(1);
	 
       }
   }

   //For debugging, print currently gotten arguments
   G4cout << "*** Got args: ***" <<G4endl;
   G4cout << "beam_energy       = " << beam_energy/MeV           << " [MeV]" << "\t\t (-e / --energy)" << G4endl;
   G4cout << "beam_sigma_x      = " << beam_sigma_x/mm           << " [mm]"  << "\t\t (-s / --sizex)"  << G4endl;
   G4cout << "beam_sigma_y      = " << beam_sigma_y/mm           << " [mm]"  << "\t\t (--sizey)"       << G4endl;
   G4cout << "beam_alpha_x      = " << beam_alpha_x                          << "\t\t (-a / --alphax)" << G4endl;
   G4cout << "beam_alpha_y      = " << beam_alpha_y                          << "\t\t (--alphay)"      << G4endl;
   G4cout << "beam_beta_x       = " << beam_beta_x/m             << " [m]"   << "\t\t (-b / --betax)"  << G4endl;
   G4cout << "beam_beta_y       = " << beam_beta_y/m             << " [m]"   << "\t\t (--betay)"       << G4endl;
   G4cout << "num_particle      = " << num_particle                          << "\t\t (-n / --number)" << G4endl;
   G4cout << "gun_z_position    = " << gun_z_position/mm         << " [mm]"  << "\t\t (not an arg)"    << G4endl;
   G4cout << "collimator        = " << (collimator?"true":"false")           << "\t\t (not an arg)"    << G4endl;
   G4cout << "collimator_radius = " << collimator_radius/mm      << " [mm]"  << "\t\t (-r / --colrad)" << G4endl;
   G4cout << "max_step_length   = " << max_step_length/mm        << " [mm]"  << "\t\t (-l / --step)"   << G4endl;
   G4cout << "useGUI            = " << (useGUI?"true":"false")               << "\t\t (-g / --gui)"    << G4endl;
   G4cout << G4endl;


   // Send only what was not taken by getopt_long onwards to G4UIexecutive
   int argc_effective = argc-optind+1;
   char** argv_effective = new char*[argc_effective];
   argv_effective[0] = argv[0]; //First arg is always executable name; this should be copied
   for (int i = optind; i < argc;i++){
       argv_effective[i+1-optind] = argv[i];
   }

   G4UIExecutive* ui = 0;
   if ( argc_effective == 1 ) {
     ui = new G4UIExecutive(argc_effective, argv_effective);
   }
   else if (argc_effective > 1) {
     G4cout<<argv_effective[0] <<"\n";
     G4cout<<argv_effective[1]; // Don't print this one unless we actually know that it is safe...
   }


  // Choose the Random engine
  G4Random::setTheSeed(time(NULL));
  G4Random::setTheEngine(new CLHEP::RanecuEngine);


 //Construct the default run manager
  // #ifdef G4MULTITHREADED
  //   G4MTRunManager* runManager = new G4MTRunManager;
  // #else
    G4RunManager* runManager = new G4RunManager;
  // #endif

  /************** Set mandatory initialization classes*************/

  // Detector construction
  detector = new DetectorConstruction(collimator,
                                      collimator_radius,
                                      max_step_length);
  runManager->SetUserInitialization(detector);
  // Physics list
  G4PhysListFactory physListFactory;
  const G4String phylistname = "QGSP_BIC_EMY";
  G4VModularPhysicsList* physicsList = physListFactory.GetReferencePhysList(phylistname);
  physicsList->RegisterPhysics(new G4StepLimiterPhysics());
  runManager->SetUserInitialization(physicsList);
  // User action initialization
  runManager->SetUserInitialization(new ActionInitialization(beam_energy,
                                                             beam_sigma_x,
                                                             beam_sigma_y,
                                                             beam_alpha_x,
                                                             beam_alpha_y,
                                                             beam_beta_x,
                                                             beam_beta_y,
                                                             collimator,
                                                             collimator_radius,
                                                             max_step_length,
                                                             gun_z_position));


  // Initialize visualization
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();

  // Get the pointer to the User Interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  // Process macro or start UI session

  if ( ! ui ) {
    // batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  }
  else {
    // interactive mode

    UImanager->ApplyCommand("/control/execute init_vis.mac");
    // UImanager->ApplyCommand("/run/beamOn 100");
    ui->SessionStart();
    delete ui;
  }

  // else{
  //   // interactive mode
  //   UImanager->ApplyCommand("/control/execute init_vis.mac");
  //   UImanager->ApplyCommand("/run/beamOn 100");
  //   ui->SessionStart();
  //   delete ui;
  // }

  // Job termination
  // Free the store: user actions, physics_list and detector_description are
  // owned and deleted by the run manager, so they should not be deleted
  // in the main() program !

  delete visManager;
  delete runManager;
}
