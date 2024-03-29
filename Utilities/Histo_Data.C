#include <vector>
//#include "DataFormats/Math/interface/deltaR.h"
#include <iostream>
#include <cmath>
#include <algorithm>
//float dr1 = deltaR(GENlep_eta->at(r),GENlep_phi->at(r), lep_eta->at(j), lep_phi->at(j));


double Start=50;
double End=150;
int bin=50;
int bin1 = 16;
double l=74;
double u=106;
double s = 250;

int PN_idx = 10; //number possibile fitting coefficinets

static const std::vector<float> PN_scores {0.83226, 0.949388, 0.981101};

int PN_DIM =  PN_scores.size(); //number of PN-MD score bins

static const std::vector<float> DDX_scores {0.0365136, 0.127416, 0.286469};

int DDX_DIM =  DDX_scores.size(); //number of DDX score bins

static const std::vector<string> functions {"Cebysev"};


void Histo_Data(){
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(0);

  //gStyle->SetOptStat(1000000001);
  //gStyle->SetOptFit(1111);

  TH1::AddDirectory(kFALSE); 
  
  std::string Y_string{"Events / "+ std::to_string(((End/s-Start/s)/bin))};
  const char * Y_title{Y_string.c_str()};

  //histogams sidebands

  //PN-MD softdropmass histograms
  TH1F *PN_Data[PN_DIM];
  
  for(int iPN=0; iPN<PN_DIM;iPN++){
    std::string nomestringa{"PNhist"+std::to_string(iPN)};
    const char * nome{nomestringa.c_str()};    
    PN_Data[iPN]= new TH1F(nome, "x", bin, Start/s, End/s);
    PN_Data[iPN]->GetXaxis()->SetTitle("x");    
    PN_Data[iPN]->GetYaxis()->SetTitle(Y_title);
    if(iPN==0){PN_Data[iPN]->SetTitle("PN-MD_BBvsQCD loose WP");}
    if(iPN==1){PN_Data[iPN]->SetTitle("PN-MD_BBvsQCD medium WP");}
    if(iPN==2){PN_Data[iPN]->SetTitle("PN-MD_BBvsQCD tight WP");}
    PN_Data[iPN]->Sumw2();  
  }

  //DDX softdropmass histograms
  TH1F *DDX_Data[PN_DIM];
  
  for(int iPN=0; iPN<DDX_DIM;iPN++){
    std::string nomestringa{"DDXhist"+std::to_string(iPN)};
    const char * nome{nomestringa.c_str()};    
    DDX_Data[iPN]= new TH1F(nome, "x", bin, Start/s, End/s);
    DDX_Data[iPN]->GetXaxis()->SetTitle("x");    
    DDX_Data[iPN]->GetYaxis()->SetTitle(Y_title);
    if(iPN==0){DDX_Data[iPN]->SetTitle("DDX_BBvsQCD loose WP");}
    if(iPN==1){DDX_Data[iPN]->SetTitle("DDX_BBvsQCD medium WP");}
    if(iPN==2){DDX_Data[iPN]->SetTitle("DDX_BBvsQCD tight WP");}
    DDX_Data[iPN]->Sumw2();  
  }

  //histogams signal region

  //PN-MD softdropmass histograms
  TH1F *PN_Data_s[PN_DIM];
  
  for(int iPN=0; iPN<PN_DIM;iPN++){
    std::string nomestringa{"PNhist"+std::to_string(iPN)+"_s"};
    const char * nome{nomestringa.c_str()};    
    PN_Data_s[iPN]= new TH1F(nome, "x", bin1, l/s, u/s);
    PN_Data_s[iPN]->GetXaxis()->SetTitle("x");    
    PN_Data_s[iPN]->GetYaxis()->SetTitle(Y_title);
    if(iPN==0){PN_Data_s[iPN]->SetTitle("PN-MD_BBvsQCD loose WP");}
    if(iPN==1){PN_Data_s[iPN]->SetTitle("PN-MD_BBvsQCD medium WP");}
    if(iPN==2){PN_Data_s[iPN]->SetTitle("PN-MD_BBvsQCD tight WP");}
    PN_Data_s[iPN]->Sumw2();  
  }

  //DDX softdropmass histograms
  TH1F *DDX_Data_s[PN_DIM];
  
  for(int iPN=0; iPN<DDX_DIM;iPN++){
    std::string nomestringa{"DDXhist"+std::to_string(iPN)+"_s"};
    const char * nome{nomestringa.c_str()};    
    DDX_Data_s[iPN]= new TH1F(nome, "x", bin1, l/s, u/s);
    DDX_Data_s[iPN]->GetXaxis()->SetTitle("x");    
    DDX_Data_s[iPN]->GetYaxis()->SetTitle(Y_title);
    if(iPN==0){DDX_Data_s[iPN]->SetTitle("DDX_BBvsQCD loose WP");}
    if(iPN==1){DDX_Data_s[iPN]->SetTitle("DDX_BBvsQCD medium WP");}
    if(iPN==2){DDX_Data_s[iPN]->SetTitle("DDX_BBvsQCD tight WP");}
    DDX_Data_s[iPN]->Sumw2();  
  }

  TChain *T_Data = new TChain("passedEvents");  // name of the tree is the argument
  T_Data->Add("/lustre/cms/store/user/dtroiano/Commissioning/Data/RunC.root");
  T_Data->Add("/lustre/cms/store/user/dtroiano/Commissioning/Data/RunD.root");
  T_Data->Add("/lustre/cms/store/user/dtroiano/Commissioning/Data/RunE.root");
  T_Data->Add("/lustre/cms/store/user/dtroiano/Commissioning/Data/RunF.root");
  T_Data->Add("/lustre/cms/store/user/dtroiano/Commissioning/Data/RunG.root");
  

  //definition of the variables and branches
  Double_t AK8_sdmJet0;
  Float_t AK8_ptJet0, PNMD_XbbVsQCD, DDX_XbbVsQCD;//pt, softdropmass and scores of the leading AK8 jet
  
  T_Data->SetBranchAddress("AK8_ptJet0", &AK8_ptJet0);
  T_Data->SetBranchAddress("AK8_sdmJet0", &AK8_sdmJet0);
  T_Data->SetBranchAddress("PNMD_XbbVsQCD", &PNMD_XbbVsQCD);
  T_Data->SetBranchAddress("DDX_XbbVsQCD", &DDX_XbbVsQCD);
    
  Int_t nentries = (Int_t)T_Data->GetEntries();

  for (int i = 0; i < nentries; i++){      
    T_Data->GetEntry(i); 

    for(int iPN=0; iPN<PN_DIM;iPN++){
      if(AK8_sdmJet0>l && AK8_sdmJet0<u && PNMD_XbbVsQCD>PN_scores.at(iPN)){PN_Data_s[iPN]->Fill(AK8_sdmJet0/s);}
       if(((AK8_sdmJet0>Start && AK8_sdmJet0<l) || (AK8_sdmJet0 >u && AK8_sdmJet0<End)) && PNMD_XbbVsQCD>PN_scores.at(iPN)){PN_Data[iPN]->Fill(AK8_sdmJet0/s);}
    } 

    for(int iPN=0; iPN<DDX_DIM;iPN++){
      if(AK8_sdmJet0>l && AK8_sdmJet0<u && DDX_XbbVsQCD>DDX_scores.at(iPN)){DDX_Data_s[iPN]->Fill(AK8_sdmJet0/s);}
      if(((AK8_sdmJet0>Start && AK8_sdmJet0<l) || (AK8_sdmJet0 >u && AK8_sdmJet0<End)) && DDX_XbbVsQCD>DDX_scores.at(iPN)){DDX_Data[iPN]->Fill(AK8_sdmJet0/s);}
    } 
    
  }

  
  //saving histograms in a Tfile

  TFile *myfile;
  myfile = TFile::Open("Data_histos.root","RECREATE");
  myfile->cd();

  for(int i=0; i<PN_DIM;i++){
    PN_Data[i]->Write();
    PN_Data_s[i]->Write();
  }

  for(int i=0; i<DDX_DIM;i++){
    DDX_Data[i]->Write();
    DDX_Data_s[i]->Write();
  }

  myfile->Close();
  delete myfile;
  //plot histograms

  //histograms for the PN-MD_BBvsQCD score
  /*
  TCanvas *PN = new TCanvas("CanvasPN", "PN", 800, 600);
  PN->cd();
  //PN->SetLogy();

  PN->Print("./Plots/PN-MD_threshold.pdf[");

  l_PNMD_BBvsQCD->Draw("histe");
  PN->Print("./Plots/PN-MD_threshold.pdf");
  PN->Clear();
  PN->cd();

  m_PNMD_BBvsQCD->Draw("histe");
  PN->Print("./Plots/PN-MD_threshold.pdf");
  PN->Clear();
  PN->cd();
  
  t_PNMD_BBvsQCD->Draw("histe");
  PN->Print("./Plots/PN-MD_threshold.pdf");
  PN->Clear();
  PN->cd();
 
  PN->Print("./Plots/PN-MD_threshold.pdf]");


  TCanvas *DDX = new TCanvas("CanvasDDX", "DDX", 800, 600);
  DDX->cd();
  //DDX->SetLogy();

  DDX->Print("./Plots/DDX_threshold.pdf[");

  l_DDX_BBvsQCD->Draw("histe");
  DDX->Print("./Plots/DDX_threshold.pdf");
  DDX->Clear();
  DDX->cd();

  m_DDX_BBvsQCD->Draw("histe");
  DDX->Print("./Plots/DDX_threshold.pdf");
  DDX->Clear();
  DDX->cd();
  
  t_DDX_BBvsQCD->Draw("histe");
  DDX->Print("./Plots/DDX_threshold.pdf");
  DDX->Clear();
  DDX->cd();
 
  DDX->Print("./Plots/DDX_threshold.pdf]");
  */


  //histograms of the all AK8 jets for PN-MD_BBvsQCD
  /*
  TCanvas *PNMD = new TCanvas("CanvasPNMD", "PNMD", 800, 600);
  PNMD->cd();
  PNMD->SetLogy();

  PNMD_BBvsQCD->SetLineColor(2);
  PNMD_BBvsQCD->SetFillColor(2);
  PNMD_BBvsQCD->SetFillStyle(3354);
  Lpt_PNMD_BBvsQCD->SetLineColor(1);
  Lpt_PNMD_BBvsQCD->SetFillColor(1);
  Lpt_PNMD_BBvsQCD->SetFillStyle(3335);
  bAK8_PNMD_BBvsQCD->SetLineColor(4);
  bAK8_PNMD_BBvsQCD->SetFillColor(4);
  bAK8_PNMD_BBvsQCD->SetFillStyle(3744);
  Lpt_bAK8_PNMD_BBvsQCD->SetLineColor(8);
  Lpt_bAK8_PNMD_BBvsQCD->SetFillColor(8);
  Lpt_bAK8_PNMD_BBvsQCD->SetFillStyle(3636);
  

  float max_PN=PNMD_BBvsQCD->GetMaximum() ;
  if(max_PN < Lpt_PNMD_BBvsQCD->GetMaximum()){max_PN=Lpt_PNMD_BBvsQCD->GetMaximum();}
  if(max_PN < bAK8_PNMD_BBvsQCD->GetMaximum()){max_PN=bAK8_PNMD_BBvsQCD->GetMaximum();}
  if(max_PN < Lpt_bAK8_PNMD_BBvsQCD->GetMaximum()){max_PN=Lpt_bAK8_PNMD_BBvsQCD->GetMaximum();}

  float min_PN=PNMD_BBvsQCD->GetMinimum() ;
  if(min_PN < Lpt_PNMD_BBvsQCD->GetMinimum()){min_PN=Lpt_PNMD_BBvsQCD->GetMinimum();}
  if(min_PN < bAK8_PNMD_BBvsQCD->GetMinimum()){min_PN=bAK8_PNMD_BBvsQCD->GetMinimum();}
  if(min_PN < Lpt_bAK8_PNMD_BBvsQCD->GetMinimum()){min_PN=Lpt_bAK8_PNMD_BBvsQCD->GetMinimum();}

  PNMD_BBvsQCD->SetMaximum(1.1*max_PN);
  PNMD_BBvsQCD->SetMinimum(0.9*min_PN);

  TH1F *frame_PNMD = new TH1F("frame_PNMD","frame_PNMD", bin, Start, End);
  frame_PNMD->SetTitle("");
  frame_PNMD->GetXaxis()->SetTitle("PN-MD_BBvsQCD");
  frame_PNMD->GetYaxis()->SetTitle("Normalized to 1");
  frame_PNMD->SetMaximum(1);
  frame_PNMD->SetMinimum(0.0004);

  frame_PNMD->Draw("hist");
  PNMD_BBvsQCD->DrawNormalized("histsame");
  Lpt_PNMD_BBvsQCD->DrawNormalized("histsame");
  Lpt_bAK8_PNMD_BBvsQCD->DrawNormalized("histsame");
  bAK8_PNMD_BBvsQCD->DrawNormalized("histsame");

  
  auto legend1 = new TLegend(0.3,0.6,0.58,0.8);  
  legend1->AddEntry( PNMD_BBvsQCD,"match","f");
  legend1->AddEntry( Lpt_PNMD_BBvsQCD, "L_pt && no-match","f");
  legend1->AddEntry( bAK8_PNMD_BBvsQCD,"no-L_pt && match","f");
  legend1->AddEntry( Lpt_bAK8_PNMD_BBvsQCD,"L_pt && match","f");
  legend1->SetBorderSize(0);
  legend1->Draw(); 
  
  
  PNMD->Print("./Plots/PNMD_scores_log.png");
  */

  //histograms of the all AK8 jets for DDX_BBvsQCD
  /*
  TCanvas *DDX = new TCanvas("CanvasDDX", "DDX", 800, 600);
  DDX->cd();
  DDX->SetLogy();

  DDX_BBvsQCD->SetLineColor(2);
  DDX_BBvsQCD->SetFillColor(2);
  DDX_BBvsQCD->SetFillStyle(3354);
  Lpt_DDX_BBvsQCD->SetLineColor(1);
  Lpt_DDX_BBvsQCD->SetFillColor(1);
  Lpt_DDX_BBvsQCD->SetFillStyle(3335);
  bAK8_DDX_BBvsQCD->SetLineColor(4);
  bAK8_DDX_BBvsQCD->SetFillColor(4);
  bAK8_DDX_BBvsQCD->SetFillStyle(3744);
  Lpt_bAK8_DDX_BBvsQCD->SetLineColor(8);
  Lpt_bAK8_DDX_BBvsQCD->SetFillColor(8);
  Lpt_bAK8_DDX_BBvsQCD->SetFillStyle(3636);
  
  TH1F *frame_DDX = new TH1F("frame_DDX","frame_DDX", bin, Start, End);
  frame_DDX->SetTitle("");
  frame_DDX->GetXaxis()->SetTitle("DDX_BBvsQCD");
  frame_DDX->GetYaxis()->SetTitle("Normalized to 1");
  frame_DDX->SetMaximum(1);
  frame_DDX->SetMinimum(0.0004);

  frame_DDX->Draw("hist");
  DDX_BBvsQCD->DrawNormalized("histsame");
  Lpt_DDX_BBvsQCD->DrawNormalized("histsame");
  Lpt_bAK8_DDX_BBvsQCD->DrawNormalized("histsame");
  bAK8_DDX_BBvsQCD->DrawNormalized("histsame");

  
  auto legend2 = new TLegend(0.3,0.6,0.58,0.8);  
  legend2->AddEntry( DDX_BBvsQCD,"match","f");
  legend2->AddEntry( Lpt_DDX_BBvsQCD, "L_pt && no-match","f");
  legend2->AddEntry( bAK8_DDX_BBvsQCD,"no-L_pt && match","f");
  legend2->AddEntry( Lpt_bAK8_DDX_BBvsQCD,"L_pt && match","f");
  legend2->SetBorderSize(0);
  legend2->Draw(); 
    
  DDX->Print("./Plots/DDX_scores_log.png");
  */


 
}
