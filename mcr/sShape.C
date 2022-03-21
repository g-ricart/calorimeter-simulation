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
    TGraph* sShapeX = new TGraph();
    sShapeX->GetXaxis()->SetTitle("xReco");
    sShapeX->GetYaxis()->SetTitle("xReco - xTrue");
    sShapeX->GetYaxis()->SetTitleOffset(1.3);

    TGraph* sShapeY = new TGraph();
    sShapeY->GetXaxis()->SetTitle("yReco");
    sShapeY->GetYaxis()->SetTitle("yReco - yTrue");
    sShapeY->GetYaxis()->SetTitleOffset(1.3);

    // Fit functions
    TF1* sin_fit_x  = new TF1("sin_fit_x", "[0]*sin([1]*x + [2])", 0, 0.1);
    sin_fit_x->SetParLimits(0, 0.0005, 0.001);
    sin_fit_x->SetLineColor(kRed);

    TF1* sin_fit_y  = new TF1("sin_fit_y", "[0]*sin([1]*x + [2])", 0, 0.1);
    sin_fit_y->SetParLimits(0, 0.0005, 0.001);
    sin_fit_y->SetLineColor(kRed);

    TF1* pol3_fit_x = new TF1("pol3_fit_x", "pol3(0)", 0, 0.1);
    pol3_fit_x->SetLineColor(kBlue);

    TF1* pol3_fit_y = new TF1("pol3_fit_y", "pol3(0)", 0, 0.1);
    pol3_fit_y->SetLineColor(kBlue);

    for (Int_t entryId = 0; entryId < inTree->GetEntries(); ++entryId) {
        inTree->GetEntry(entryId);

        // Fill graph
        sShapeX->SetPoint(sShapeX->GetN(), xReco, xReco - xTrue);
        sShapeY->SetPoint(sShapeY->GetN(), yReco, yReco - yTrue);
    }

    // X fits
    sShapeX->Fit(sin_fit_x,  "OE");
    sShapeX->Fit(pol3_fit_x, "OE");
    // Y fits
    sShapeY->Fit(sin_fit_y,  "OE");
    sShapeY->Fit(pol3_fit_y, "OE");

    TCanvas* c1 = new TCanvas("c1", "", 0, 0, 1000, 800);
    sShapeX->Draw("AP");
    sin_fit_x->Draw("same");
    pol3_fit_x->Draw("same");

    auto legendX = new TLegend(0.1,0.7,0.48,0.9);
    legendX->AddEntry("sin_fit_x",  Form("sinus fit, chi2: %f",
                                       sin_fit_x->GetChisquare()), "l");
    legendX->AddEntry("pol3_fit_x", Form("pol3 fit, chi2: %f",
                                       pol3_fit_x->GetChisquare()), "l");
    legendX->Draw("same");

    TCanvas* c2 = new TCanvas("c2", "", 0, 0, 1000, 800);
    sShapeY->Draw("AP");
    sin_fit_y->Draw("same");
    pol3_fit_y->Draw("same");

    auto legendY = new TLegend(0.1,0.7,0.48,0.9);
    legendY->AddEntry("sin_fit_y",  Form("sinus fit, chi2: %f",
                                       sin_fit_y->GetChisquare()), "l");
    legendY->AddEntry("pol3_fit_y", Form("pol3 fit, chi2: %f",
                                       pol3_fit_y->GetChisquare()), "l");
    legendY->Draw("same");

    c1->Update();
    c2->Update();
}
