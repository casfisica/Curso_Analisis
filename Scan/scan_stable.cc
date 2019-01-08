#include <iostream>
#include <stdlib.h> 
#include "ROOTFunctions.h"
#include "DelphesFunctions.h"
#include "scan.h"

using namespace std;

// Global variables
double pi = 4.0*atan(1.0);

double monojetcut=110.0;

// begining of the program
int main(int argc, char *argv[]) {
  
  // read list of cuts to be applied
  ifstream cuts;
  char cname[10];
  string str;
  int nmuonpt,njets,nljetpt,nmet,nmt,ndphi;
  double muonptcut[20];
  double njetscut[20];
  double ljetptcut[20];
  double metcut[20];
  double mtcut[20];
  double dphicut[20];
  cuts.open("CUTSINFO.DAT");  
  std::getline(cuts,str);
  cuts>>cname>>nmuonpt;
  for (int i=0;i<nmuonpt;i++) cuts>>muonptcut[i];
  cuts>>cname>>njets;
  for (int i=0;i<njets;i++) cuts>>njetscut[i];
  cuts>>cname>>nljetpt;
  for (int i=0;i<nljetpt;i++) cuts>>ljetptcut[i];
  cuts>>cname>>nmet;
  for (int i=0;i<nmet;i++) cuts>>metcut[i];
  cuts>>cname>>nmt;
  for (int i=0;i<nmt;i++) cuts>>mtcut[i];
  cuts>>cname>>ndphi;
  for (int i=0;i<ndphi;i++) cuts>>dphicut[i];
  cuts.close();


  // Open Tchain inside Delphes
  TChain chain("Delphes");
  chain.Add(argv[1]);    
  
  // Create object of class ExRootTreeReader
  ExRootTreeReader *treeReader = new ExRootTreeReader(&chain);
  
  // Number of entries access
  long int numberOfEntries = treeReader->GetEntries();
  
  // Get pointers to branches used in this analysis 
  TClonesArray *branchJet = treeReader->UseBranch("Jet");
  TClonesArray *branchMuon = treeReader->UseBranch("Muon");
  TClonesArray *branchMissingET = treeReader->UseBranch("MissingET");


  // Loop over all events
    
   int cutflow[10]={10*0};
   int scan6[10][10][10][10][10][10]={1000000*0};
   int scan5[10][10][10][10][10]={100000*0};
   int scan4[10][10][10][10]={10000*0};
   int scan3[10][10][10]={1000*0};
   int scan2[10][10]={100*0};
   int scan1[10]={10*0};
  
   int nshow=10000;
   
   //  std::cout<<" Total events = "<<numberOfEntries<<endl;
  for ( Int_t entry = 0; entry < numberOfEntries; ++entry ){
    
    // Load selected branches with data from specified event
    if (entry%nshow == 0 || entry ==numberOfEntries-1)
       {
	 std::cout<<" # events processed ="<<entry<<std::endl;
       } 
    
    cutflow[0]++;
    treeReader->ReadEntry(entry);
    int Numjets = branchJet->GetEntries();     
    int NumMuons = branchMuon->GetEntries();
    int NMET= branchMuon->GetEntries();
   //Creating pointer for each particle
    MissingET *metpointer;
    Muon *muonpointer;
    Jet *jeti;
    metpointer = (MissingET*)branchMissingET->At(0);
    muonpointer = (Muon*)branchMuon->At(0);
    int nbtags=0;

    int njets30=0;
    double htx=0.0;
    double hty=0.0;
    double htz=0.0;
    double mht=0.0;
    double ht=0.0;
    double mt_mumet,mt_jetmet,mt_mujet,rmumet,rjetmet,rmujet;
    double dphi_mujet, dphi_mumet,dphi_jetmet;
    double leadingpt;

    if (NMET<1) continue;
    for(Int_t i = 0; i < Numjets; i++){
      jeti = (Jet*) branchJet->At(i);      
      ht+=jeti->PT;
      double theta=2.0*atan(exp(-jeti->Eta));
      double phii=pi+jeti->Phi;
      htx+=jeti->PT*cos(phii);
      hty+=jeti->PT*sin(phii);
    }
    
    // test: change trigger cuts from 110 to monojetcut
//emulate monojet trigger: MET>110 GeV and MHT>110 GeV
    mht=sqrt(htx*htx+hty*hty);
    
    cutflow[1]++;
    //if ((metpointer->MET<=110)||(mht<=110)) continue;
    if ((metpointer->MET<=monojetcut)||(mht<=monojetcut)) continue;
    cutflow[2]++;  // # events after trigger condition
    
    if(NumMuons==1&&Numjets>0){
      cutflow[3]++;     
      dphi_mumet=fmod((2*pi+muonpointer->Phi-metpointer->Phi),2*pi);
      //dphi_mumet=muonpointer->Phi-metpointer->Phi;
      //if (dphi_mumet>pi) {dphi_mumet-=2*pi;}
      //else if (dphi_mumet<pi) { dphi_mumet+=2*pi;}

      mt_mumet=sqrt(2*muonpointer->PT*metpointer->MET*(1-cos(dphi_mumet)));
      if (metpointer->MET>0) rmumet=muonpointer->PT/metpointer->MET;
      for(Int_t i = 0; i < 1; i++){

	jeti = (Jet*) branchJet->At(i);
	if (i==0) {  // leading jet condition
	  leadingpt=jeti->PT;
	  dphi_mujet=fmod((2*pi+muonpointer->Phi-jeti->Phi),2*pi);
	  dphi_jetmet=fmod((2*pi+jeti->Phi-metpointer->Phi),2*pi);
	  
	  mt_mujet=sqrt(2*muonpointer->PT*jeti->PT*(1-cos(dphi_mujet)));
	  mt_jetmet=sqrt(2*jeti->PT*metpointer->MET*(1-cos(dphi_jetmet)));
	  if (metpointer->MET>0) rjetmet=jeti->PT/metpointer->MET;
	  if (jeti->PT>0) rmujet=muonpointer->PT/jeti->PT;
	}
      }      
  //      if (Numjets>0){

	cutflow[4]++;
	for (int i1=0;i1<nmuonpt;i1++){ //loop over pt cuts
	  if (muonpointer->PT<muonptcut[i1]) {
	    scan1[i1]++;
	    for (int i2=0;i2<njets;i2++){ //loop over njets cuts
	      if (Numjets<=njetscut[i2]) {
		scan2[i1][i2]++;
		for (int i3=0;i3<nljetpt;i3++){ //loop leading jet pt cuts
		  if (leadingpt>ljetptcut[i3]) {
		    scan3[i1][i2][i3]++;
		    for (int i4=0;i4<nmet;i4++){ //loop over met cuts
		      if (metpointer->MET>metcut[i4]) {
			scan4[i1][i2][i3][i4]++;
			cutflow[5]++;
			for (int i5=0;i5<nmt;i5++){ //loop over mt cuts
			  if (mt_mumet<mtcut[i5]) {
			    scan5[i1][i2][i3][i4][i5]++;
			    for (int i6=0;i6<ndphi;i6++){ //loop over dphi cuts
			      if (fabs(dphi_mumet-pi)>=dphicut[i6]) {
				scan6[i1][i2][i3][i4][i5][i6]++;
				cutflow[6]++;
			      } //if of dphi cut6
			    } //loop over dphi cut
			  } //if of mt cut5
			} //loop over mt cut		       
		      } //if of met cut4
		    } //loop over met cut		   
		  } //if of leading jet pt cut3
		} //loop over leading jet pt cut	       
	      } //if of njets cut2
	    } //loop over njets cut
	  } //if of muon pt cut1
	} //loop over pt cuts
	//      }//if numjets>0

   }//IF NMUONS==1
  
  } //end loop over entries
  
  
  ofstream outfile("OUTFILE.TXT");
  
  for (int i1=0;i1<nmuonpt;i1++){ //loop over pt cuts
    scan1[i1];
    for (int i2=0;i2<njets;i2++){ //loop over njets cuts
      scan2[i1][i2];
      for (int i3=0;i3<nljetpt;i3++){ //loop leading jet pt cuts
	scan3[i1][i2][i3];
	for (int i4=0;i4<nmet;i4++){ //loop over met cuts
	  scan4[i1][i2][i3][i4];
	  for (int i5=0;i5<nmt;i5++){ //loop over mt cuts
	    scan5[i1][i2][i3][i4][i5];
	    for (int i6=0;i6<ndphi;i6++){ 
	      outfile<<i1<<" "<<i2<<" "<<i3<<" "<<i4<<" "<<i5<<" "<<i6<<" "<<cutflow[0]<<" "<<cutflow[1]<<" ";
	      //	      outfile<<cutflow[2]<<" "<<cutflow[3]<<" "<<cutflow[5]<<"  "<<cutflow[6]<<" "<<scan1[i1]<<" "<<scan2[i1][i2]<<" "<<scan3[i1][i2][i3]<<" ";
	      outfile<<cutflow[2]<<" "<<cutflow[6]<<" "<<scan1[i1]<<" "<<scan2[i1][i2]<<" "<<scan3[i1][i2][i3]<<" ";
	      outfile<<scan4[i1][i2][i3][i4]<<" "<<scan5[i1][i2][i3][i4][i5]<<" "<<scan6[i1][i2][i3][i4][i5][i6]<<endl;
	      //	      cout<<"### debug: before & after mtcut: "<<scan4[i1][i2][i3][i4]<<" & "<<scan6[i1][i2][i3][i4][i5][i6]<<endl;
	    }
	  }
	}
      }
    }
  }
  
  outfile.close();
  cout<<"######################### CUT FLOW SUMMARY ###############"<<endl;
cout<<"                         TOTAL NUMBER OF EVENTS  [0] = "<<cutflow[0]<<endl;
//cout<<" ------------------------------------------------------------"<<endl;
 cout<<" At least 1 muon                    [1] = "<<cutflow[1]<< "   ; relative eff.    ="<<float(cutflow[1])/float(cutflow[0])<<endl;
 cout<<" MET>"<<monojetcut<<", MHT>"<<monojetcut<<"                   [2] = "<<cutflow[2]<< "   ; relative eff.    ="<<float(cutflow[2])/float(cutflow[1])<<endl;
 cout<<" Exactly 1 muon                     [3] = "<<cutflow[3]<< "   ; relative eff.    ="<<float(cutflow[3])/float(cutflow[2])<<endl;
 //cout<<" nJETS>0                            [3] = "<<cutflow[3]<< "   ; relative eff. ="<<float(cutflow[3])/float(cutflow[2])<<endl;
 //cout<<" MET>"<<monojetcut<<", MHT>"<<monojetcut<<"  & Exacly 1 muon  [1] = "<<cutflow[4]<< "   ; relative eff.    ="<<float(cutflow[4])/float(cutflow[0])<<endl;
 cout<<" cuts except MT                     [5] = "<<cutflow[5]<< "   ; relative eff.    ="<<float(cutflow[5])/float(cutflow[3])<<endl;
 cout<<" All cuts                           [6] = "<<cutflow[6]<< "   ; total eff.    ="<<float(cutflow[6])/float(cutflow[0])<<endl;
cout<<"####################################################################"<<endl;

  
} //end program


    


 


 





   

