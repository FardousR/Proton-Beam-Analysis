


#include "RunAction.hh"
#include "PrimaryGeneratorAction.hh"
#include "DetectorConstruction.hh"
#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4AccumulableManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"


RunAction::RunAction(G4String output, G4double beam_energy_input) : G4UserRunAction(), OutputFile(output), Energy(beam_energy_input)
{
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    analysisManager->SetVerboseLevel(1);

    G4double alpha = 1.9*pow(10, -3);
    G4double p = 1.8;
    G4double range = alpha*pow(1.1*Energy, p);

    G4int max_depth = (G4int)(range * 10)+10;

    G4double x_num   = 1000,   x_min   = -50,  x_max   = 50;
    G4double y_num   = 200,    y_min   = -50,  y_max   = 50;
    G4double z_num   = 800,    z_min   = 0.0,  z_max   = 200;
    G4double r_num   = 500,    r_min   = 0.0,  r_max   = 50;
    G4double KE_num  = 160,    KE_min  = 0.0,  KE_max  = 160000000;
    G4double LET_num = 200,    LET_min = 0.0,  LET_max = 10.0;

    //AllEnergyHistoID       =  analysisManager->CreateH3("AllEnergyHisto", "Energy Deposition by Particles",    400, -200.0, 200.0, 400, -200.0, 200.0, 200, 0., 200.0);
    ProtonEnergyHistoID      =  analysisManager->CreateH3("ProtonEnergyHisto", "Energy Deposition(Proton)",
                                x_num, x_min, x_max, y_num, y_min, y_max, z_num, z_min, z_max);
    ProtonLongEnergyHistoID  =  analysisManager->CreateH1("ProtonLongEnergyHisto", "Energy Deposition(Proton)", z_num, z_min, z_max);
    // ProtonEnergyZHistoID     =  analysisManager->CreateH1("ProtonEnergyHisto", "Energy Deposition(Proton)", z_num, z_min, z_max);
    ProtonRadialHistoID      =  analysisManager->CreateH2("ProtonRadialHisto", "Energy Radial Deposition(Proton)",
                                z_num, z_min, z_max, r_num, r_min, r_max);

    ProtonKEHistoID          =  analysisManager->CreateH2("ProtonKEHisto", "Kinetic Energy(Proton)",
                                z_num, z_min, z_max, KE_num, KE_min, KE_max);
    NeutronKEHistoID         =  analysisManager->CreateH2("NeutronEnergyHisto",  "Energy Deposition by Neutrons",
                                z_num, z_min, z_max, KE_num, KE_min, KE_max);
    // ElectronEnergyHistoID  =  analysisManager->CreateH3("ElectronEnergyHisto", "Energy Deposition by Electron",     400, -200.0, 200.0, 400, -200.0, 200.0, 200, 0., 200.0);

    ParticlecountZ0HistID     =  analysisManager->CreateH1("ParticelCounter",    "Number of Particles at Water Surface", 5, 0, 5);
    ProtonFluenceHistoID      =  analysisManager->CreateH1("ProtonFluence",      "Number of Proton with depth", 200, 0, 200);
    Proton1FluenceHistoID     =  analysisManager->CreateH1("Proton1Fluence",     "Number of Proton with depth", 200, 0, 200);
    Proton2FluenceHistoID     =  analysisManager->CreateH1("Proton2Fluence",     "Number of Proton with depth", 200, 0, 200);
    Proton3FluenceHistoID     =  analysisManager->CreateH1("Proton3Fluence",     "Number of Proton with depth", 200, 0, 200);
    Proton4FluenceHistoID     =  analysisManager->CreateH1("Proton4Fluence",     "Number of Proton with depth", 200, 0, 200);
    Proton5FluenceHistoID     =  analysisManager->CreateH1("Proton5Fluence",     "Number of Proton with depth", 200, 0, 200);
    Proton8FluenceHistoID     =  analysisManager->CreateH1("Proton8Fluence",     "Number of Proton with depth", 200, 0, 200);
    Proton10FluenceHistoID    =  analysisManager->CreateH1("Proton10Fluence",    "Number of Proton with depth", 200, 0, 200);
    Proton15FluenceHistoID    =  analysisManager->CreateH1("Proton15Fluence",    "Number of Proton with depth", 200, 0, 200);
    Proton20FluenceHistoID    =  analysisManager->CreateH1("Proton20Fluence",    "Number of Proton with depth", 200, 0, 200);
    Proton25FluenceHistoID    =  analysisManager->CreateH1("Proton25Fluence",    "Number of Proton with depth", 200, 0, 200);

    //ProtonLongFluenceHistoID    =  analysisManager->CreateH1("ProtonLongFluence" , "Number of Proton with depth", 200, 0, 200);
    //ProtonLETdataHistoID      =  analysisManager->CreateH1("ProtonLETdataHisto", "LET data(Protons)",z_num, z_min, z_max);

    LETDisHistoID             =  analysisManager->CreateH2("LETHisto", "Proton LET Histo",
                                 z_num, z_min, z_max, 150, 0.0, 15.0 );
    LETDataHistoID            =  analysisManager->CreateH1("LETDataHisto", "Proton LET Histo",  z_num, z_min, z_max);
    LETData3DHistoID          =  analysisManager->CreateH3("LETData3DHisto", "Proton LET 3D Histo",
                                 x_num, x_min, x_max, y_num, y_min, y_max, z_num, z_min, z_max);
    NeutronFluenceHistoID     =  analysisManager->CreateH1("NeutronFluence", "Number of Neutron with depth", 200, 0, 200);
}

RunAction::~RunAction()
{

}

void RunAction::BeginOfRunAction(const G4Run* run)
{

    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

    analysisManager->OpenFile(OutputFile);

}

void RunAction::EndOfRunAction(const G4Run* run)
{
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    analysisManager->Write();
    analysisManager->CloseFile();
}
