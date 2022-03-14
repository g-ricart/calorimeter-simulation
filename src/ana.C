void ana(TString file_path)
{
    // macro to plot distributions from the Event tree

    // Fetch TTree
    TFile* inFile = TFile::Open(file_path);
    TTree* inTree = (TTree*)inFile->Get("eventTree");

    // Set branch adresses.
    Int_t eventNumber;
    Float_t eReco;
    Float_t eTrue;
    inTree->SetBranchAddress("eventNumber", &eventNumber);
    inTree->SetBranchAddress("eReco",       &eReco);
    inTree->SetBranchAddress("eTrue",       &eTrue);

    // Create histogram
    TH1F* resolution = new TH1F("hist_reso", "Resolution distribution", 100, -1, 1);

    // Loop over tree entries.
    for (Int_t entryId = 0; entryId < inTree->GetEntries(); ++entryId) {
        inTree->GetEntry(entryId);

        // Fill histograms
        resolution->Fill(eReco - eTrue);
    }

    // Outputs
    cout <<  inFile << endl; // check the pointer to the root file
    cout <<  inTree << endl; // check the pointer to the the tree
    cout << "Number of Entries in tree : " << inTree->GetEntries() << endl;
    inTree->Draw("eTrue");

    // Draw histograms
    TCanvas* c1 = new TCanvas("c1", "", 0, 0, 1000, 800);
    resolution->Draw();
    c1->Update();
}
