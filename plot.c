#include <TTree.h>
#include <TFile.h>
#include <TH1D.h>
void Neutron_Energy_distribution()
{
      // gStyle->SetOptStat(0.1);
      TCanvas* c1 = new TCanvas("c1", "  ");
      TFile* rootfile  = new TFile("pfBSA.root");          
      TH1D* histo_neutron = (TH1D*)rootfile->Get("neutrons_after");
      histo_neutron->SetMarkerStyle(4);
      histo_neutron->Scale(1e-6);
      histo_neutron->SetLineColor(kBlack);
      histo_neutron->Draw("HIST c l");
        histo_neutron->SetTitle("(C,Pb) M=15cm R=15cm; Energy#(){MeV} ;Neutron #(){per particle} ");
      c1->cd();
      c1->Update(); 
}
void plot() 
{ 
	Neutron_Energy_distribution();
}

