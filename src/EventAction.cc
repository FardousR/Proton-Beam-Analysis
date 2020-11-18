
#include "EventAction.hh"
#include "RunAction.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include <sstream>
#include <string>
#include <iostream>
#include <ostream>
#include <fstream>
#include "Analysis.hh"
#include <math.h>

EventAction::EventAction(RunAction* runAction):G4UserEventAction(), fRunAction(runAction)
{
}

EventAction::~EventAction()
{

}

void EventAction::BeginOfEventAction(const G4Event*)
{
	ClearTrackData(); //Clear data from TrackData vectors
}

void EventAction::EndOfEventAction(const G4Event* Event)
{
	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

	for (G4int i=0;i<ParticleID.size();++i)
	{
		G4double DoseLETData =0, CalLET = 0;
		G4double pre_x = PrePosition[i].getX()*mm;
		G4double pre_y = PrePosition[i].getY()*mm;
		G4double pre_z = PrePosition[i].getZ()*mm;

		G4double post_x = PostPosition[i].getX()*mm;
		G4double post_y = PostPosition[i].getY()*mm;
		G4double post_z = PostPosition[i].getZ()*mm;

    G4double energy_dipo_x = pre_x + (post_x - pre_x) * ( (G4double)rand() / (G4double)RAND_MAX );
    G4double energy_dipo_y = pre_y + (post_y - pre_y) * ( (G4double)rand() / (G4double)RAND_MAX );
		G4double energy_dipo_z = pre_z + (post_z - pre_z) * ( (G4double)rand() / (G4double)RAND_MAX );
		G4double radial_distance = sqrt(pow(energy_dipo_x,2) + pow(energy_dipo_y,2));
		G4double pre_r  = sqrt(pow(pre_x,2) + pow(pre_y,2));
		G4double post_r = sqrt(pow(post_x,2) + pow(post_y,2));

		if(pre_z == 0)
		{
			analysisManager->FillH1(fRunAction->GetParticlecountZ0HistID(), (ParticleID[i]-0.5), 1);
		}

		if(ParticleID[i] == 1)
		{
			analysisManager->FillH3(fRunAction->GetProtonEnergyHistoID(), energy_dipo_x, energy_dipo_y, energy_dipo_z, EnergyDeposit[i]);
			analysisManager->FillH1(fRunAction->GetProtonLongEnergyHistoID(), energy_dipo_z, EnergyDeposit[i]);
			//analysisManager->FillH1(fRunAction->GetProtonEnergyZHistoID(), energy_dipo_z, EnergyDeposit[i]);
			analysisManager->FillH2(fRunAction->GetProtonRadialHistoID(), energy_dipo_z, radial_distance, EnergyDeposit[i]);
			analysisManager->FillH2(fRunAction->GetProtonKEHistoID(),   pre_z,   PreKE[i],  1);

      if((int)pre_z!=(int)post_z)
				{

					    G4double ra = pre_r + (((post_r-pre_r)/(post_z-pre_z))*((int)post_z-pre_z));
				      analysisManager->FillH1(fRunAction->GetProtonFluenceHistoID(), post_z-.5, 1);
							if(ra<1){
								analysisManager->FillH1(fRunAction->GetProton1FluenceHistoID(), post_z-.5, 1);
							}
							if(ra<2){
								analysisManager->FillH1(fRunAction->GetProton2FluenceHistoID(), post_z-.5, 1);
							}

							if(ra<3){
								analysisManager->FillH1(fRunAction->GetProton3FluenceHistoID(), post_z-.5, 1);
							}
							if(ra<4){
								analysisManager->FillH1(fRunAction->GetProton4FluenceHistoID(), post_z-.5, 1);
							}
							if(ra<5){
								analysisManager->FillH1(fRunAction->GetProton5FluenceHistoID(), post_z-.5, 1);
							}
							if(ra<8){
								analysisManager->FillH1(fRunAction->GetProton8FluenceHistoID(), post_z-.5, 1);
							}
							if(ra<10){
								analysisManager->FillH1(fRunAction->GetProton10FluenceHistoID(), post_z-.5, 1);
							}
							if(ra<15){
								analysisManager->FillH1(fRunAction->GetProton15FluenceHistoID(), post_z-.5, 1);
							}
							if(ra<20){
								analysisManager->FillH1(fRunAction->GetProton20FluenceHistoID(), post_z-.5, 1);
							}
							if(ra<25){
								analysisManager->FillH1(fRunAction->GetProton25FluenceHistoID(), post_z-.5, 1);
							}
							//analysisManager->FillH1(fRunAction->GetProtonLongFluenceHistoID(), post_z-.5,  1);
			  }


			if(StepLength[i]==0)
				{
			   DoseLETData = 0;
				 CalLET  = 0;
				}
			else
			  {
			   DoseLETData = (EnergyDeposit[i]*EnergyDeposit[i])/StepLength[i];
				 CalLET  = EnergyDeposit[i]/StepLength[i];
			  }
			analysisManager->FillH2(fRunAction->GetLETDisHistoID(),   energy_dipo_z,    CalLET/1000000,    1);
			//analysisManager->FillH3(fRunAction->GetProtonLETdataHistoID(), energy_dipo_x, energy_dipo_y, energy_dipo_z, DoseLET);
			analysisManager->FillH1(fRunAction->GetLETDataHistoID(),   energy_dipo_z, DoseLETData);
			analysisManager->FillH3(fRunAction->GetLETData3DHistoID(), energy_dipo_x, energy_dipo_y, energy_dipo_z, DoseLETData);
    }

		else if(ParticleID[i] == 5)
		{
			analysisManager->FillH2(fRunAction->GetNeutronKEHistoID(),  pre_z,   PreKE[i],  1);
      if((int)pre_z!=(int)post_z)
				{
					analysisManager->FillH1(fRunAction->GetNeutronFluenceHistoID(), post_z-.5,  1);
			  }
		}
	}
ClearTrackData();
}
