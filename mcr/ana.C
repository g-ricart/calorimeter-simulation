void ana(TString file_path)
{
    // macro to plot distributions from the Event tree

    // Fetch TTree
    TFile* inFile = TFile::Open(file_path);
    TTree* inTree = (TTree*)inFile->Get("eventTree");

    // Set branch addresses.
    Int_t eventNumber;
    Float_t eReco;
    Float_t eTrue;
    Float_t eRecoBias;
    inTree->SetBranchAddress("eventNumber", &eventNumber);
    inTree->SetBranchAddress("eReco",       &eReco);
    inTree->SetBranchAddress("eTrue",       &eTrue);
    inTree->SetBranchAddress("eRecoBias",   &eRecoBias);

    // Create histograms
    TH1F* resolution = new TH1F("hist_reso", "Resolution distribution", 100, -1, 1);
    resolution->GetXaxis()->SetTitle("eRecoBias - eTrue [GeV]");
    resolution->SetStats(0);

    // Fit functions
    TF1* fit_gaus = new TF1("fit_gaus", "gaus", -999, 999);
    fit_gaus->SetLineColor(kRed);

    // Loop over tree entries.
    for (Int_t entryId = 0; entryId < inTree->GetEntries(); ++entryId) {
        inTree->GetEntry(entryId);

        // Fill histograms
        resolution->Fill(eRecoBias - eTrue);
    }

    // Fit histograms
    resolution->Fit(fit_gaus, "E");

    // Get fit parameters
    auto chi2      = fit_gaus->GetChisquare();
    auto ndof      = fit_gaus->GetNDF();
    auto mean      = fit_gaus->GetParameter(1);
    auto sigma     = fit_gaus->GetParameter(2);
    auto sigma_err = fit_gaus->GetParError(2);

    // Outputs
    cout <<  inFile << endl; // check the pointer to the root file
    cout <<  inTree << endl; // check the pointer to the the tree
    cout << "Number of Entries in tree : " << inTree->GetEntries() << endl;
    //inTree->Draw("eTrue");

    // Draw histograms
    TCanvas* c1 = new TCanvas("c1", "", 0, 0, 1000, 800);
    resolution->Draw();
    fit_gaus->Draw("same");
    c1->Update();
}
