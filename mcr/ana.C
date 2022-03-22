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
    eReso->GetYaxis()->SetTitle("Nb of events");

    TH1F* xResoRaw = new TH1F("hist_xResoRaw",
                              "X raw resolution distribution",
                              100, -0.003, 0.003);
    xResoRaw->GetXaxis()->SetTitle("xReco - xTrue [m]");
    xResoRaw->GetYaxis()->SetTitle("Nb of events");

    TH1F* yResoRaw = new TH1F("hist_yResoRaw",
                              "Y raw resolution distribution",
                              100, -0.003, 0.003);
    yResoRaw->GetXaxis()->SetTitle("yReco - yTrue [m]");
    yResoRaw->GetYaxis()->SetTitle("Nb of events");

    TH1F* xResoCor = new TH1F("hist_xResoCor",
                              "X corrected resolution distribution",
                              100, -0.003, 0.003);
    xResoCor->GetXaxis()->SetTitle("xReco - xTrue [m]");
    xResoCor->GetYaxis()->SetTitle("Nb of events");

    TH1F* yResoCor = new TH1F("hist_yResoCor",
                              "Y corrected resolution distribution",
                              100, -0.003, 0.003);
    yResoCor->GetXaxis()->SetTitle("yReco - yTrue [m]");
    yResoCor->GetYaxis()->SetTitle("Nb of events");

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

    // Outputs
    cout <<  inFile << endl; // check the pointer to the root file
    cout <<  inTree << endl; // check the pointer to the the tree
    cout << "Number of Entries in tree : " << inTree->GetEntries() << endl;
    //inTree->Draw("eTrue");

    // Draw histograms
    TCanvas* c1 = new TCanvas("c1", "", 0, 0, 1000, 800);
    auto legendE = new TLegend(0.1,0.7,0.48,0.9);
    legendE->AddEntry(eReso->GetFunction("fit_eReso"), "Gaussian fit", "l");
    eReso->Draw();
    eReso->GetFunction("fit_eReso")->Draw("same");
    legendE->Draw("draw");
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

    inTree->GetEntry(5);

    TCanvas* c6 = new TCanvas("c6", "", 0, 0, 1000, 800);
    histZ->SetTitle("Deposited energy along Z axis");
    histZ->GetXaxis()->SetTitle("Layer index");
    histZ->GetYaxis()->SetTitle("Deposited energy [GeV]");
    histZ->SetStats(0);
    histZ->Draw();
    c6->Update();

    TCanvas* c7 = new TCanvas("c7", "", 0, 0, 1000, 800);
    c7->SetLogz();

    histXY->SetTitle("Deposited energy in transverse plane");
    histXY->GetXaxis()->SetTitle("X cell index");
    histXY->GetYaxis()->SetTitle("Y cell index");
    histXY->GetZaxis()->SetTitle("Deposited energy [GeV]");
    histXY->SetStats(0);

    TMarker* impactPointReco = new TMarker((xRecoCor - CalConst::XYMin)/CalConst::XYSize,
                                           (yRecoCor - CalConst::XYMin)/CalConst::XYSize,
                                           43);
    impactPointReco->SetMarkerSize(2);
    impactPointReco->SetMarkerColor(kRed);

    auto legend = new TLegend(0.1,0.7,0.48,0.9);
    legend->AddEntry(impactPointReco, "Reconstructed impact point", "p");

    histXY->Draw("colz");
    impactPointReco->Draw("same");
    c7->Update();
    legend->Draw("same");

    TCanvas* c8 = new TCanvas("c7", "", 0, 0, 1000, 800);
    histXY->Draw("lego2 0");
    histXY->GetXaxis()->SetTitleOffset(1.7);
    histXY->GetYaxis()->SetTitleOffset(1.7);
    histXY->GetZaxis()->SetTitleOffset(1.3);
    c8->Update();

}
