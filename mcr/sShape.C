#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TF1.h"
#include "TString.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TMath.h"

#include "../src/CaloConstants.h"

void sShape(TString file_path)
{
    // macro to plot distributions from the Event tree

    // Fetch TTree
    TFile* inFile = TFile::Open(file_path);
    TTree* inTree = (TTree*)inFile->Get("eventTree");

    // Set branch addresses
    int eventNumber;
    float eTrue;
    float eReco;
    float eRecoBias;
    float xTrue;
    float yTrue;
    float xReco;
    float yReco;
    TH1F* histZ  = new TH1F();
    TH2F* histXY = new TH2F();
    inTree->SetBranchAddress("eventNumber", &eventNumber);
    inTree->SetBranchAddress("eTrue",       &eTrue);
    inTree->SetBranchAddress("eReco",       &eReco);
    inTree->SetBranchAddress("eRecoBias",   &eRecoBias);
    inTree->SetBranchAddress("xTrue",       &xTrue);
    inTree->SetBranchAddress("yTrue",       &yTrue);
    inTree->SetBranchAddress("xReco",       &xReco);
    inTree->SetBranchAddress("yReco",       &yReco);
    inTree->SetBranchAddress("histZ",       &histZ);
    inTree->SetBranchAddress("histXY",      &histXY);

    // S-Shape graph
    TGraph* sShape = new TGraph();

    // Fit functions
    TF1* sin_fit  = new TF1("sin_fit", "[0]*sin([1]*x + [2])", -0.1, 0);
    sin_fit->SetParLimits(0, 0, 0.001);
    sin_fit->SetLineColor(kRed);
    TF1* pol3_fit = new TF1("pol3_fit", "pol3(0)", -0.1, 0);
    pol3_fit->SetLineColor(kBlue);

    for (Int_t entryId = 0; entryId < inTree->GetEntries(); ++entryId) {
        inTree->GetEntry(entryId);

        // Fill graph
        sShape->SetPoint(sShape->GetN(), xReco, xReco - xTrue);
    }

    sShape->Fit(sin_fit,  "OE");
    sShape->Fit(pol3_fit, "OE");

    TCanvas* c1 = new TCanvas("c1", "", 0, 0, 1000, 800);
    sShape->Draw("AP");
    sin_fit->Draw("same");
    pol3_fit->Draw("same");

    auto legend = new TLegend(0.1,0.7,0.48,0.9);
    legend->AddEntry("sin_fit",  Form("sinus fit, chi2: %f",
                                      sin_fit->GetChisquare()), "l");
    legend->AddEntry("pol3_fit", Form("pol3 fit, chi2: %f",
                                      pol3_fit->GetChisquare()), "l");
    legend->Draw("same");

    c1->Update();
}
