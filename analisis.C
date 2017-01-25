
#include <iostream>
#include <string>
using namespace std;


void analisis(void)
{
  /*Cargo la librería de Delphes*/
  gSystem->Load("/home/camilo/Proyectos/Delphes/delphes/libDelphes.so");

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
    }else{
    }
    //convierto en cadena de caracteres constante (es lo que recibe la función)
    const char * c = out.c_str();
    /*pego todos los datos*/
    MainChain.Add(c);
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
  /*Hago un loop sobre el numero de entradas*/
  


for(Int_t entry = 0; entry < numberOfEntries; ++entry)
  {
    // Se carga un evento espesifico para ser analizado
    treeReader->ReadEntry(entry);

    // Se hace el primer corte, se pide que tenga al menos dos jets
    if(branchJet->GetEntries() > 1)
    {
      // Take first jet
      Jet *jet = (Jet*) branchJet->At(0);

      // Plot jet transverse momentum
      histJetPT->Fill(jet->PT);

      // Print jet transverse momentum
      cout << "Jet pt: "<<jet->PT << endl;
    }

    Electron *elec1, *elec2;

    // If event contains at least 2 electrons
    if(branchElectron->GetEntries() > 1)
    {
      // Take first two electrons
      elec1 = (Electron *) branchElectron->At(0);
      elec2 = (Electron *) branchElectron->At(1);

      // Plot their invariant mass
      histMass->Fill(((elec1->P4()) + (elec2->P4())).M());
    }
  }


  
}
