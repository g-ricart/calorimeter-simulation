#include "Event.h"
#include "CaloSimulation.h"
#include "ShowerConstants.h"

#include "TH1F.h"
#include "TH2F.h"
#include "TCanvas.h"

void ana_simu(const Event& event)
{
    // Get calorimeter data from event.
    CaloSimulation::CalData calData = event.calData();

    // List of layer energies
    float layerEnergies[CalConst::NbLayers] = {0.};

    for (auto const& it: calData){ // iterate over caldata map
        auto cellAddress = it.first;  // get cell adresses (keys of the map)
        auto cell        = it.second; // get cells (values of the map)

        int currentLayer = cellAddress.layer(); // Indentify layer of current cell
        layerEnergies[currentLayer] += cell.energy(); // Add energy of current
                                                      // cell to the layer
    }

    TH1F* histoZ = new TH1F("histoZ", "Longitudinal energy loss",
                            CalConst::NbLayers, 0, CalConst::NbLayers + 1);
    for (size_t i = 0; i < sizeof(layerEnergies)/sizeof(layerEnergies[0]); i++){
        histoZ->SetBinContent(i+1, layerEnergies[i]);
    }

    TCanvas* c1 = new TCanvas("c1", "", 0, 0, 1000, 800);
    histoZ->Draw();
    c1->Update();
}
