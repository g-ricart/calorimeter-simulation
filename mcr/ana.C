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
    float xRecoCor;
    float yRecoCor;
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
    inTree->SetBranchAddress("xRecoCor",    &xRecoCor);
    inTree->SetBranchAddress("yRecoCor",    &yRecoCor);
    inTree->SetBranchAddress("histZ",       &histZ);
    inTree->SetBranchAddress("histXY",      &histXY);

    // Create histograms
    TH1F* eReso = new TH1F("hist_eReso",
                           "Energy resolution distribution",
                           100, -1, 1);
    eReso->GetXaxis()->SetTitle("eReco - eTrue [GeV]");

    TH1F* xResoRaw = new TH1F("hist_xResoRaw",
                              "X raw resolution distribution",
                              100, -0.003, 0.003);
    xResoRaw->GetXaxis()->SetTitle("xReco - xTrue [m]");

    TH1F* yResoRaw = new TH1F("hist_yResoRaw",
                              "Y raw resolution distribution",
                              100, -0.003, 0.003);

    TH1F* xResoCor = new TH1F("hist_xResoCor",
                              "X corrected resolution distribution",
                              1000, -1, 1);

    TH1F* yResoCor = new TH1F("hist_yResoCor",
                              "Y corrected resolution distribution",
                              100, -0.003, 0.003);

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
        xResoRaw->Fill(xReco - xTrue);
        yResoRaw->Fill(yReco - yTrue);
        xResoCor->Fill(xRecoCor - xTrue);
        yResoCor->Fill(yRecoCor - yTrue);
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
    xResoRaw->Draw();
    c2->Update();

    TCanvas* c3 = new TCanvas("c3", "", 0, 0, 1000, 800);
    yResoRaw->Draw();
    c3->Update();

    TCanvas* c4 = new TCanvas("c4", "", 0, 0, 1000, 800);
    xResoCor->Draw();
    c4->Update();

    TCanvas* c5 = new TCanvas("c5", "", 0, 0, 1000, 800);
    yResoCor->Draw();
    c5->Update();
}
