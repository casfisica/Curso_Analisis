
#ifdef __CLING__
R__LOAD_LIBRARY(libDelphes)
#include "classes/DelphesClasses.h"
#include "external/ExRootAnalysis/ExRootTreeReader.h"
#endif

#include <iostream>
#include <string>
#include <math.h>       /* cosh, log */
using namespace std;


void analisis(void)
{
  /*Cargo la librería de Delphes*/
  // gSystem->Load("/home/camilo/Proyectos/Delphes/delphes/libDelphes.so");

  /*Instancio un objeto TChain*/
  TChain chain("Delphes");

  /*Creo las variables necesarias para el for*/

  std::string nom1="/Storage/scratch/camilo/Proyectos/MadGraph/Datos/Signal_prueba-2/Events/run_";
  std::string nom2="/tag_1_delphes_events.root";
  std::string num, out;


  /*Llenado del chain con todos los runs*/
  for ( i=3; i<100; i=i+1 ) {
    num = std::to_string(i);
    
    if( i < 10 ) {
      out= nom1+"0"+num+nom2;
    }
    //convierto en cadena de caracteres constante (es lo que recibe la función)
    const char * c = out.c_str();
    /*pego todos los datos*/
    chain.Add(c);
  }

  //Creo un objeto de treereader, que recive la dirección en memoria de
  //la cadena (TChain) como argumento
  ExRootTreeReader *treeReader = new ExRootTreeReader(&chain);
  /*Leo el numero de entradas*/
  Long64_t numberOfEntries = treeReader->GetEntries();
  /*Obtengo las ramas que deseo*/
  TClonesArray *branchMuon = treeReader->UseBranch("Muon");
  TClonesArray *branchMissingET = treeReader->UseBranch("MissingET");
  TClonesArray *branchJet = treeReader->UseBranch("Jet");

  // Inicializo los histogramas
  TH1 *histJetPT = new TH1F("jet_pt", "jet P_{T}", 100, 0.0, 100.0);
  TH1 *histMass = new TH1F("mass", "M_{inv}(e_{1}, e_{2})", 100, 40.0, 140.0);



  //COMIENZO DEL ANÁLISIS

  // Inicializo los contadores
  Int_t cut1=0, cut2=0, cut3=0, cut4=0, cut5=0;

  /*Hago un loop sobre el numero de entradas*/

  for(Int_t entry = 0; entry < numberOfEntries; ++entry)
    {
      // Se carga un evento espesifico para ser analizado
      treeReader->ReadEntry(entry);
      
      // Se hace el primer corte, se pide que tenga al menos dos jets
      if(branchJet->GetEntries() > 1)
        {
	  ++cut1; //Cuantos eventos pasan el corte 1
	  // se toma el primer jet y se hace un cast a la clase Jet
	  Jet *jet1 = (Jet*) branchJet->At(0);
	  Jet *jet2 = (Jet*) branchJet->At(1);
	  
	  if( jet1->BTag>0 && jet2->BTag>0 )
            {
	      ++cut2; //Cuantos eventos pasan el corte 2
	      //Inicializo los obejos clase muon
	      Muon *muon1, *muon2;
	      
	      // Para ser contados deben de tener al menos 2 muones
	      if(branchMuon->GetEntries() > 1)
                {
		  ++cut3; //Cuantos eventos pasan el corte 3
		  // Take first two electrons, tomo solo dos porque estan organizados por PT
		  muon1 = (Muon *) branchMuon->At(0);
		  muon2 = (Muon *) branchMuon->At(1);
		  //Si la carga es diferente
		  int charge = muon1->Charge * muon2->Charge;
		  if( charge < 0 )
                    {
		      ++cut4; //Cuantos eventos pasan el corte 4
		      
		      double MassMuon=(muon1->P4()+muon2->P4()).M();
		      if( !((MassMuon<80)&&(MassMuon>100)) )
                        {
			  ++cut5; //Cuantos eventos pasan el corte 4
			  
                          
			  // Plot jet transverse momentum
			  //histJetPT->Fill(jet->PT);
			  // Plot their invariant mass
			  //histMass->Fill(((elec1->P4()) + (elec2->P4())).M());
			  
			  
			  
                        }
                    }
                }
            }
        }
    }


  std::cout<<"numberOfEntries"<<numberOfEntries<<std::endl;
  std::cout<<"cut1"<cut1<<std::endl;
  std::cout<<"cut2"<cut2<<std::endl;
  std::cout<<"cut3"<cut3<<std::endl;
  std::cout<<"cut4"<cut4<<std::endl;
  std::cout<<"cut5"<cut5<<std::endl;



  
}//End Void
