////////////////////////////////////////////////////////////////////////
//
//             A simple example with a ROOT tree
//             =================================
//
//  This program creates :
//    - a ROOT file
//    - a tree
// One possible argument : number of events
//   ---Running/Linking instructions----
//  This program consists of the following files and procedures.
//    - Event.h event class description
//    - Event.C event class implementation
//    - MainEvent.C the main program to demo this class might be used (this file)
//
//   ---Analyzing the event.root file with the interactive root
//        example of a simple session
//   Root > TFile f("Event.root")
//   Root > eventTree.Draw("eTrue") // histogram true x
//   Root > eventTree.Draw("eReco:eTrue", "eventNumber<10") // histogram E reco vs E true for first 10 events
//
////////////////////////////////////////////////////////////////////////

#include <cstdlib>
#include <iostream>

#include "TFile.h"
#include "TRandom3.h"
#include "TTree.h"
#include "TStopwatch.h"
#include "TH1F.h"
#include "TH2F.h"

#include "Event.h"
#include "CellAddress.h"
#include "CaloCell.h"
#include "CaloGeometry.h"
#include "CaloSimulation.h"
#include "CaloConstants.h"
#include "ShowerConstants.h"

using namespace std;

void reconstruct(Event& event,
                 TF1*   fitFunc,
                 float* xCenterArray,
                 float* yCenterArray,
                 float* layerCenterArray);
void simulate(Event& event, CaloSimulation& caloSim);
void ana_simu(Event& event);

bool gPrintViaErrorHandler = true; // Force Minuit to silence.

//______________________________________________________________________________
int main(int argc, char **argv)
{
    // By default create 400 events.
    int nEventsMax = 400;
    // If command line argument provided, take it as max number of events.
    if (argc > 1) nEventsMax = atoi(argv[1]);

    // Create a new ROOT binary machine independent file.
    // Note that this file may contain any kind of ROOT objects, histograms,
    // pictures, graphics objects, detector geometries, tracks, events, etc..
    // This file is now becoming the current directory.
    TFile* outFile = new TFile("EventAlt.root", "RECREATE");

    // Create a ROOT Tree and the branches to be written.
    // The instruction "Branch" tells ROOT that the value stored in this variable
    // should be written in the tree when the TTree::Fill() method is called.
    // The first arg of Branch is the name given in the Tree, the second is the
    // address of the variable to be written.
    // !!! You should add similar groups of lines if you want to store other
    // variables in the output tree.
    TTree* outTree = new TTree("eventTree", "Calo sim root tree");
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
    outTree->Branch("eventNumber",    &eventNumber);
    outTree->Branch("eTrue",          &eTrue);
    outTree->Branch("eReco",          &eReco);
    outTree->Branch("eRecoBias",      &eRecoBias);
    outTree->Branch("xTrue",          &xTrue);
    outTree->Branch("yTrue",          &yTrue);
    outTree->Branch("xReco",          &xReco);
    outTree->Branch("yReco",          &yReco);
    outTree->Branch("xRecoCor",       &xRecoCor);
    outTree->Branch("yRecoCor",       &yRecoCor);
    outTree->Branch("histZ",  "TH1F", &histZ);
    outTree->Branch("histXY", "TH2F", &histXY);

    // Create a dummy event that will be build in the loop.
    Event event;

    // Build calorimeter,
    // defined here to avoid building it for each event.
    // passed to simulate().
    CaloSimulation caloSim;
    caloSim.CalorimeterData();

    // Arrays to store XYZ cell centers,
    // defined here to avoid building them for each event.
    // Passed to reconstruct().
    float layerCenterArray[CalConst::NbLayers] = {0.};
    float xCenterArray[CalConst::NbCellsInXY]  = {0.};
    float yCenterArray[CalConst::NbCellsInXY]  = {0.};

    CaloGeometry caloGeometry;
    caloGeometry.layerCenters(layerCenterArray);
    caloGeometry.xCenters(xCenterArray);
    caloGeometry.yCenters(yCenterArray);

    // Function to recontruct impact point,
    // defined here to avoid building it for each event.
    // Passed to reconstruct().
    TF1* gausFit = new TF1("gausFit", "gaus(0)", CalConst::XYMin,
                                                 CalConst::XYMax);
    gausFit->SetParName(0, "const");
    gausFit->SetParName(1, "mean");
    gausFit->SetParName(2, "sigma");
    gausFit->SetParLimits(1, CalConst::XYMin, CalConst::XYMax);

    // Loop over the events.
    for (eventNumber = 0; eventNumber < nEventsMax; eventNumber++) {
        if (eventNumber % 100 == 0) {
            // Just to check everything is going smoothly.
            cout << "Doing event: " << eventNumber << endl;
        }

        // initialize event
        event.build(eventNumber);

        // simulation
        simulate(event, caloSim);
        ana_simu(event);

        // reconstruction
        reconstruct(event, gausFit, xCenterArray,
                                    yCenterArray,
                                    layerCenterArray);

        // Prepare to fill the output tree.
        eTrue       = event.eTrue();
        eReco       = event.eReco();
        eRecoBias   = event.eRecoBias();
        xTrue       = event.xTrue();
        yTrue       = event.yTrue();
        xReco       = event.xReco();
        yReco       = event.yReco();
        xRecoCor    = event.xRecoCor();
        yRecoCor    = event.yRecoCor();
        histZ       = event.histZ();
        histXY      = event.histXY();
        outTree->Fill(); // Fill the tree.
    } // End event loop

    outFile->cd(); // Make sure we are in the outupt file.
    outFile->Write(); // Write all current in the current directory.
    outTree->Print();

    outFile->Close();

    // Check CellAddress implementation
    CellAddress cell = CellAddress(40, 4, 0);
    cout << "(" << cell.ix() << ", " << cell.iy() << ", " << cell.layer() << ")" << endl;
    cout << cell.IsValid() << endl;

    // Check CaloCell implementation
    CaloCell cell_e = CaloCell(cell, 0.3, 0.2);
    cout << "true energy = " << cell_e.energyTrue() << endl;
    cout << "measured energy = " << cell_e.energyMeas() << endl;
    cout << "address = " << cell_e.address() << endl;

    // Check CaloGeometry implementation
    double xyz[3] = {0., 0., 0.};
    CaloGeometry caloGeo = CaloGeometry();
    cout << caloGeo.IsInside(xyz, cell) << endl;
    cout << "Center of cell : (" << caloGeo.xCentre(cell) << ", "
                                 << caloGeo.yCentre(cell) << ", "
                                 << caloGeo.zCentre(cell) << ")" << endl;

    // Check CaloSimulation::CalorimeterData implementation
    CaloSimulation testCaloSim = CaloSimulation();
    testCaloSim.CalorimeterData();
    //cout << caloSim << endl;

    // Check CaloSimulation::SimulateShower implementation
    testCaloSim.SimulateShower(0, 0, 50);
    //cout << caloSim << endl;

    return 0;
}
