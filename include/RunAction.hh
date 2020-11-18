
#ifndef RunAction_h
#define RunAction_h 1

#include "G4UserRunAction.hh"
#include "G4Accumulable.hh"
#include "globals.hh"
#include "Analysis.hh"

class G4Run;

class RunAction : public G4UserRunAction
{
  public:
    RunAction(G4String output);
    virtual ~RunAction();

    // virtual G4Run* GenerateRun();
    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);

    G4int GetAllEnergyHistoID()            {  return AllEnergyHistoID;            }
    G4int GetProtonEnergyHistoID()         {  return ProtonEnergyHistoID;         }
    G4int GetProtonLongEnergyHistoID()     {  return ProtonLongEnergyHistoID;     }
    G4int GetProtonRadialHistoID()         {  return ProtonRadialHistoID;         }
    G4int GetProtonEnergyZHistoID()        {  return ProtonEnergyZHistoID;        }
    G4int GetNeutronKEHistoID()            {  return NeutronKEHistoID;            }
    G4int GetElectronEnergyHistoID()       {  return ElectronEnergyHistoID;       }
    G4int GetProtonLETdataHistoID()        {  return ProtonLETdataHistoID;        }
    G4int GetParticlecountZ0HistID()       {  return ParticlecountZ0HistID;       }
    G4int GetLETDisHistoID()               {  return LETDisHistoID;               }
    G4int GetLETDataHistoID()              {  return LETDataHistoID;              }
    G4int GetLETData3DHistoID()            {  return LETData3DHistoID;            }

    G4int GetProtonFluenceHistoID()        {  return ProtonFluenceHistoID;        }
    G4int GetProton1FluenceHistoID()       {  return Proton1FluenceHistoID;       }
    G4int GetProton2FluenceHistoID()       {  return Proton2FluenceHistoID;       }
    G4int GetProton3FluenceHistoID()       {  return Proton3FluenceHistoID;       }
    G4int GetProton4FluenceHistoID()       {  return Proton4FluenceHistoID;       }
    G4int GetProton5FluenceHistoID()       {  return Proton5FluenceHistoID;       }
    G4int GetProton8FluenceHistoID()       {  return Proton8FluenceHistoID;       }
    G4int GetProton10FluenceHistoID()      {  return Proton10FluenceHistoID;      }
    G4int GetProton15FluenceHistoID()      {  return Proton15FluenceHistoID;      }
    G4int GetProton20FluenceHistoID()      {  return Proton20FluenceHistoID;      }
    G4int GetProton25FluenceHistoID()      {  return Proton25FluenceHistoID;      }

    G4int GetNeutronFluenceHistoID()       {  return NeutronFluenceHistoID;       }
    G4int GetProtonKEHistoID()             {  return ProtonKEHistoID;             }

  private:
    G4int AllEnergyHistoID;
    G4int ProtonEnergyHistoID;
    G4int ProtonLongEnergyHistoID;
    G4int ProtonRadialHistoID;
    G4int ProtonEnergyZHistoID;
    G4int NeutronKEHistoID;
    G4int ElectronEnergyHistoID;
    G4int ProtonLETdataHistoID;
    G4int ParticlecountZ0HistID;
    G4int LETDisHistoID;
    G4int LETDataHistoID;
    G4int LETData3DHistoID;

    G4int ProtonFluenceHistoID;
    G4int Proton1FluenceHistoID;
    G4int Proton2FluenceHistoID;
    G4int Proton3FluenceHistoID;
    G4int Proton4FluenceHistoID;
    G4int Proton5FluenceHistoID;
    G4int Proton8FluenceHistoID;
    G4int Proton10FluenceHistoID;
    G4int Proton15FluenceHistoID;
    G4int Proton20FluenceHistoID;
    G4int Proton25FluenceHistoID;

    G4int NeutronFluenceHistoID;
    G4int ProtonKEHistoID;

    G4String OutputFile;
};

#endif
