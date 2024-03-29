#include <vector>
//#include "DataFormats/Math/interface/deltaR.h"
#include <iostream>
#include <cmath>
#include <algorithm>
//float dr1 = deltaR(GENlep_eta->at(r),GENlep_phi->at(r), lep_eta->at(j), lep_phi->at(j));

/*
double Start=50;
double End=150;
int bin=50;
double l=74;
double u=106;
*/

void score_match(){
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(0);
  TH1::AddDirectory(kFALSE); 

  double Start=0;
  double End=1;
  int bin=100;

  //histograms of the AK8 jets which minimize the distances from the two b-quarks
  TH1F *DDX_BBvsQCD = new TH1F("DDX_BBvsQCD", "DDX_BBvsQCD", bin, Start, End);
  DDX_BBvsQCD->SetTitle("");
  DDX_BBvsQCD->GetXaxis()->SetTitle("BBvsQCD score");
  std::string Y_string{"Events / "+ std::to_string(((End-Start)/bin))};
  const char * Y_title{Y_string.c_str()};
  DDX_BBvsQCD->GetYaxis()->SetTitle(Y_title);
  DDX_BBvsQCD->Sumw2();
  TH1F *PNMD_BBvsQCD = new TH1F("PNMD_BBvsQCD","PNMD_BBvsQCD", bin, Start, End);
  PNMD_BBvsQCD->SetTitle("");
  PNMD_BBvsQCD->GetXaxis()->SetTitle("BBvsQCD score");
  PNMD_BBvsQCD->GetYaxis()->SetTitle(Y_title);
  PNMD_BBvsQCD->Sumw2();

  //histograms of the leading-pt AK8 jets which do not minimize the distances from the two b-quarks
  TH1F *Lpt_DDX_BBvsQCD = new TH1F("Lpt_DDX_BBvsQCD", "L_ptDDX_BBvsQCD", bin, Start, End);
  Lpt_DDX_BBvsQCD->SetTitle("");
  Lpt_DDX_BBvsQCD->GetXaxis()->SetTitle("BBvsQCD score"); 
  Lpt_DDX_BBvsQCD->GetYaxis()->SetTitle(Y_title);
  Lpt_DDX_BBvsQCD->Sumw2();
  TH1F *Lpt_PNMD_BBvsQCD = new TH1F("Lpt_PNMD_BBvsQCD","Lpt_PNMD_BBvsQCD", bin, Start, End);
  Lpt_PNMD_BBvsQCD->SetTitle("");
  Lpt_PNMD_BBvsQCD->GetXaxis()->SetTitle("BBvsQCD score");
  Lpt_PNMD_BBvsQCD->GetYaxis()->SetTitle(Y_title);
  Lpt_PNMD_BBvsQCD->Sumw2();

  //histograms of the leading-pt AK8 jets which minimize the distances from the two b-quarks
  TH1F *Lpt_bAK8_DDX_BBvsQCD = new TH1F("Lpt_bAK8_DDX_BBvsQCD", "L_bAK8_ptDDX_BBvsQCD", bin, Start, End);
  Lpt_bAK8_DDX_BBvsQCD->SetTitle("");
  Lpt_bAK8_DDX_BBvsQCD->GetXaxis()->SetTitle("BBvsQCD score"); 
  Lpt_bAK8_DDX_BBvsQCD->GetYaxis()->SetTitle(Y_title);
  Lpt_bAK8_DDX_BBvsQCD->Sumw2();
  TH1F *Lpt_bAK8_PNMD_BBvsQCD = new TH1F("Lpt_bAK8_PNMD_BBvsQCD","Lpt_bAK8_PNMD_BBvsQCD", bin, Start, End);
  Lpt_bAK8_PNMD_BBvsQCD->SetTitle("");
  Lpt_bAK8_PNMD_BBvsQCD->GetXaxis()->SetTitle("BBvsQCD score");
  Lpt_bAK8_PNMD_BBvsQCD->GetYaxis()->SetTitle(Y_title);
  Lpt_bAK8_PNMD_BBvsQCD->Sumw2();

   //histograms of the non-leading-pt AK8 jets which minimize the distances from the two b-quarks
  TH1F *bAK8_DDX_BBvsQCD = new TH1F("bAK8_DDX_BBvsQCD", "bAK8_DDX_BBvsQCD", bin, Start, End);
  bAK8_DDX_BBvsQCD->SetTitle("");
  bAK8_DDX_BBvsQCD->GetXaxis()->SetTitle("BBvsQCD score"); 
  bAK8_DDX_BBvsQCD->GetYaxis()->SetTitle(Y_title);
  bAK8_DDX_BBvsQCD->Sumw2();
  TH1F *bAK8_PNMD_BBvsQCD = new TH1F("bAK8_PNMD_BBvsQCD","bAK8_PNMD_BBvsQCD", bin, Start, End);
  bAK8_PNMD_BBvsQCD->SetTitle("");
  bAK8_PNMD_BBvsQCD->GetXaxis()->SetTitle("BBvsQCD score");
  bAK8_PNMD_BBvsQCD->GetYaxis()->SetTitle(Y_title);
  bAK8_PNMD_BBvsQCD->Sumw2();

  TChain *T_Zqq = new TChain("passedEvents");  // name of the tree is the argument
  T_Zqq->Add("/lustre/cms/store/user/dtroiano/Commissioning/MC/ZJetsToQQ_HT200to400.root");
  T_Zqq->Add("/lustre/cms/store/user/dtroiano/Commissioning/MC/ZJetsToQQ_HT400to600.root");
  T_Zqq->Add("/lustre/cms/store/user/dtroiano/Commissioning/MC/ZJetsToQQ_HT600to800.root");
  T_Zqq->Add("/lustre/cms/store/user/dtroiano/Commissioning/MC/ZJetsToQQ_HT800toInf.root");
  T_Zqq->Add("/lustre/cms/store/user/dtroiano/Commissioning/MC/ZJetsToQQ_HT200to400_postEE.root");
  T_Zqq->Add("/lustre/cms/store/user/dtroiano/Commissioning/MC/ZJetsToQQ_HT400to600_postEE.root");
  T_Zqq->Add("/lustre/cms/store/user/dtroiano/Commissioning/MC/ZJetsToQQ_HT600to800_postEE.root");
  T_Zqq->Add("/lustre/cms/store/user/dtroiano/Commissioning/MC/ZJetsToQQ_HT800toInf_postEE.root");


  //definition of the variables and branches
  Float_t AK8_ptJet0, PNMD_XbbVsQCD, DDX_XbbVsQCD;//pt and scores of the leading AK8 jet
  Double_t lumiWeight;

  Int_t idx_BestZqq_AK8;

  std::vector<float> *AK8_pt = 0;
  std::vector<float> *probXbb = 0;
  std::vector<float> *probQCDbb_md = 0;
  std::vector<float> *probQCDcc_md = 0;
  std::vector<float> *probQCDb_md = 0;
  std::vector<float> *probQCDc_md = 0;
  std::vector<float> *probQCDo_md = 0;  
  std::vector<float> *probHbb_ddx = 0;
  

  T_Zqq->SetBranchAddress("AK8_ptJet0", &AK8_ptJet0);
  T_Zqq->SetBranchAddress("PNMD_XbbVsQCD", &PNMD_XbbVsQCD);
  T_Zqq->SetBranchAddress("DDX_XbbVsQCD", &DDX_XbbVsQCD);
  T_Zqq->SetBranchAddress("lumiWeight", &lumiWeight);

  T_Zqq->SetBranchAddress("idx_BestZqq_AK8", &idx_BestZqq_AK8);
    
  T_Zqq->SetBranchAddress("AK8PuppiJets_pt",&AK8_pt);
  T_Zqq->SetBranchAddress("jet_pfMassDecorrelatedParticleNetJetTags_probXbb",&probXbb);
  T_Zqq->SetBranchAddress("jet_pfMassDecorrelatedParticleNetJetTags_probQCDbb",&probQCDbb_md);
  T_Zqq->SetBranchAddress("jet_pfMassDecorrelatedParticleNetJetTags_probQCDcc",&probQCDcc_md);
  T_Zqq->SetBranchAddress("jet_pfMassDecorrelatedParticleNetJetTags_probQCDb",&probQCDb_md);
  T_Zqq->SetBranchAddress("jet_pfMassDecorrelatedParticleNetJetTags_probQCDc",&probQCDc_md);
  T_Zqq->SetBranchAddress("jet_pfMassDecorrelatedParticleNetJetTags_probQCDothers",&probQCDo_md);
  T_Zqq->SetBranchAddress("jet_pfMassIndependentDeepDoubleBvLV2JetTags_probHbb",&probHbb_ddx);


  Int_t nentries = (Int_t)T_Zqq->GetEntries();

  float A=0;
  float B=0;
  float tot=0;

  for (int i = 0; i < nentries; i++){      
    T_Zqq->GetEntry(i); 

    if(idx_BestZqq_AK8>-1){
      tot = tot + lumiWeight;
      Float_t BestZbbAK8_pt, BestZbbPNMD_XbbVsQCD, BestZbbDDX_XbbVsQCD;//pt and scores of the AK8 jet which minimizes the distances from the two b-quarks

      BestZbbAK8_pt = AK8_pt->at(idx_BestZqq_AK8);
      BestZbbPNMD_XbbVsQCD = probXbb->at(idx_BestZqq_AK8)/(probXbb->at(idx_BestZqq_AK8)+probQCDbb_md->at(idx_BestZqq_AK8)+probQCDcc_md->at(idx_BestZqq_AK8)+probQCDb_md->at(idx_BestZqq_AK8)+probQCDc_md->at(idx_BestZqq_AK8)+probQCDo_md->at(idx_BestZqq_AK8));//PN-MD Xbb vs QCD
      BestZbbDDX_XbbVsQCD =probHbb_ddx->at(idx_BestZqq_AK8);//DDX Xbb vs QCD

      DDX_BBvsQCD->Fill(BestZbbDDX_XbbVsQCD, lumiWeight);
      PNMD_BBvsQCD->Fill(BestZbbPNMD_XbbVsQCD, lumiWeight);

      if(AK8_ptJet0>BestZbbAK8_pt){
	A=A+lumiWeight;
	Lpt_DDX_BBvsQCD->Fill(DDX_XbbVsQCD, lumiWeight);
	Lpt_PNMD_BBvsQCD->Fill(PNMD_XbbVsQCD, lumiWeight);
	bAK8_DDX_BBvsQCD->Fill(BestZbbDDX_XbbVsQCD, lumiWeight);
	bAK8_PNMD_BBvsQCD->Fill(BestZbbPNMD_XbbVsQCD, lumiWeight);
      }
      else{
	B = B +lumiWeight;
	Lpt_bAK8_DDX_BBvsQCD->Fill(BestZbbDDX_XbbVsQCD, lumiWeight);
	Lpt_bAK8_PNMD_BBvsQCD->Fill(BestZbbPNMD_XbbVsQCD, lumiWeight);
      }
    }
    
  }

  //cout<<"Su "<<tot<<" eventi si ha che in "<<A<<" l'AK8 leading in pt non coincide con quello più vicino ai quark b"<<endl;
  //cout<<B<<endl;


  //plot histograms

  //histograms of the AK8 jets which minimize the distances from the two b-quarks
  /*
  TCanvas *Z = new TCanvas("CanvasZ", "Z", 800, 600);
  Z->cd();
  Z->SetLogy();

  DDX_BBvsQCD->SetLineColor(2);
  DDX_BBvsQCD->SetFillColor(2);
  DDX_BBvsQCD->SetFillStyle(3335);
  PNMD_BBvsQCD->SetLineColor(4);
  PNMD_BBvsQCD->SetFillColor(4);
  PNMD_BBvsQCD->SetFillStyle(3354);

  float max=DDX_BBvsQCD->GetMaximum() ;
  if(max < PNMD_BBvsQCD->GetMaximum()){max=PNMD_BBvsQCD->GetMaximum();}

  DDX_BBvsQCD->SetMaximum(1.1*max);
  DDX_BBvsQCD->Draw("hist");
  PNMD_BBvsQCD->Draw("histsame");

  auto legend = new TLegend(0.3,0.6,0.58,0.8);
  legend->AddEntry( DDX_BBvsQCD,"DDX_BBvsQCD","f");
  legend->AddEntry( PNMD_BBvsQCD,"PN-MD_BBvsQCD","f");
  legend->SetBorderSize(0);
  legend->Draw(); 

  Z->Print("./Plots/BestZqq_scores.png");
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


  //WPs evaluation
  const Int_t nq = 10;
  Double_t yq[nq];  // position where to compute the quantiles in [0,1]
  Double_t xq[nq];  // array to contain the quantiles in [min,max]
  for (Int_t i=0;i<nq;i++) {yq[i] = Float_t(i+1)/nq;}

  PNMD_BBvsQCD->GetQuantiles(nq,xq,yq);
  //Lpt_bAK8_PNMD_BBvsQCD->GetQuantiles(nq,xq,yq);
  cout<<"PN-MD_BBvsQCD"<<endl;
  for(int i=0;i<nq;i++){
    cout<<xq[i]<<endl;
    cout<<yq[i]<<endl;
  }

  DDX_BBvsQCD->GetQuantiles(nq,xq,yq);
  //Lpt_bAK8_DDX_BBvsQCD->GetQuantiles(nq,xq,yq);
  cout<<"DDX_BBvsQCD"<<endl;
  for(int i=0;i<nq;i++){
    cout<<xq[i]<<endl;
    cout<<yq[i]<<endl;
  }

  TCanvas *Z = new TCanvas("CanvasZ", "Z", 800, 600);
  Z->cd();
  //Z->SetLogy();

  Lpt_bAK8_DDX_BBvsQCD->SetLineColor(4);
  Lpt_bAK8_DDX_BBvsQCD->SetFillColor(4);
  Lpt_bAK8_DDX_BBvsQCD->SetFillStyle(3354);
  Lpt_bAK8_PNMD_BBvsQCD->SetLineColor(4);
  Lpt_bAK8_PNMD_BBvsQCD->SetFillColor(4);
  Lpt_bAK8_PNMD_BBvsQCD->SetFillStyle(3354);

  Z->Print("./Plots/Best_Lpt_Zqq_scores.pdf[");
  Z->cd();
  Lpt_bAK8_DDX_BBvsQCD->Draw("hist");
  Z->Print("./Plots/Best_Lpt_Zqq_scores.pdf");
  Z->Clear();
  Z->cd();
  Lpt_bAK8_PNMD_BBvsQCD->Draw("hist");
  Z->Print("./Plots/Best_Lpt_Zqq_scores.pdf");
  

  Z->Print("./Plots/Best_Lpt_Zqq_scores.pdf]");
}
