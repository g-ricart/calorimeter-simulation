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

void reconstruct(Event& event);
void simulate(Event& event);
void ana_simu(Event& event);

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
    TFile* outFile = new TFile("Event.root", "RECREATE");

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
    TH1F* histZ  = new TH1F();
    TH2F* histXY = new TH2F();
    outTree->Branch("eventNumber",    &eventNumber);
    outTree->Branch("eTrue",          &eTrue);
    outTree->Branch("eReco",          &eReco);
    outTree->Branch("eRecoBias",      &eRecoBias);
    outTree->Branch("histZ",  "TH1F", &histZ);
    outTree->Branch("histXY", "TH2F", &histXY);

    // Create a dummy event that will be build in the loop.
    Event event;

    // Loop over the events.
    for (eventNumber = 0; eventNumber < nEventsMax; eventNumber++) {
        if (eventNumber % 100 == 0) {
            // Just to check everything is going smoothly.
            cout << "Doing event: " << eventNumber << endl;
        }

        // initialize event
        event.build(eventNumber);

        // simulation
        simulate(event);
        ana_simu(event);

        // reconstruction
        reconstruct(event);

        // Prepare to fill the output tree.
        eTrue     = event.eTrue();
        eReco     = event.eReco();
        eRecoBias = event.eRecoBias();
        histZ     = event.histZ();
        histXY    = event.histXY();
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
    CaloCell cell_e = CaloCell(cell, 0.3);
    cout << "energy = " << cell_e.energy() << endl;
    cout << "address = " << cell_e.address() << endl;

    // Check CaloGeometry implementation
    double xyz[3] = {0., 0., 0.};
    CaloGeometry caloGeo = CaloGeometry();
    cout << caloGeo.IsInside(xyz, cell) << endl;
    cout << "Center of cell : (" << caloGeo.xCentre(cell) << ", "
                                 << caloGeo.yCentre(cell) << ", "
                                 << caloGeo.zCentre(cell) << ")" << endl;

    // Check CaloSimulation::CalorimeterData implementation
    CaloSimulation caloSim = CaloSimulation();
    caloSim.CalorimeterData();
    //cout << caloSim << endl;

    // Check CaloSimulation::SimulateShower implementation
    caloSim.SimulateShower(0, 0, 50);
    //cout << caloSim << endl;

    return 0;
}
