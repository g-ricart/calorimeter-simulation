#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TMath.h"

#include "../src/CaloConstants.h"

void ana(TString file_path)
{
    // macro to plot distributions from the Event tree

    // Fetch TTree
    TFile* inFile = TFile::Open(file_path);
    TTree* inTree = (TTree*)inFile->Get("eventTree");

    // Set branch addresses.
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

    // Create histograms
    TH1F* eReso = new TH1F("hist_eReso",
                           "Energy resolution distribution",
                           100, -1, 1);
    eReso->GetXaxis()->SetTitle("eReco - eTrue [GeV]");

    TH1F* xReso = new TH1F("hist_xReso",
                           "X resolution distribution",
                           100, -CalConst::XYSize*10, CalConst::XYSize*10);
    xReso->GetXaxis()->SetTitle("xReco - xTrue [m]");

    // Fit functions
    TF1* fit_gaus = new TF1("fit_gaus", "gaus(0)",
                            -999, 999);
    fit_gaus->SetNpx(10000);
    fit_gaus->SetParLimits(1, CalConst::XYMin, CalConst::XYMax);
    fit_gaus->SetParName(0, "const");
    fit_gaus->SetParName(1, "mean");
    fit_gaus->SetParName(2, "sigma");
    fit_gaus->SetLineColor(kRed);

    // Loop over tree entries.
    for (Int_t entryId = 0; entryId < inTree->GetEntries(); ++entryId) {
        inTree->GetEntry(entryId);

        // Fill histograms
        eReso->Fill(eReco - eTrue);
        xReso->Fill(xReco - xTrue);
    }

    // Fit histograms
    auto eResoFitResults = eReso->Fit((TF1*)fit_gaus->Clone("fit_eReso"), "OE");
    // auto xResoFitResults = xReso->Fit((TF1*)fit_gaus->Clone("fit_xReso"), "E");

    // Outputs
    cout <<  inFile << endl; // check the pointer to the root file
    cout <<  inTree << endl; // check the pointer to the the tree
    cout << "Number of Entries in tree : " << inTree->GetEntries() << endl;
    //inTree->Draw("eTrue");

    // Draw histograms
    TCanvas* c1 = new TCanvas("c1", "", 0, 0, 1000, 800);
    eReso->Draw();
    eReso->GetFunction("fit_eReso")->Draw("same");
    c1->Update();

    TCanvas* c2 = new TCanvas("c2", "", 0, 0, 1000, 800);
    xReso->Draw();
    // xReso->GetFunction("fit_xReso")->Draw("same");
    c2->Update();
}
