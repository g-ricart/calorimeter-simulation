#include "Event.h"
#include "CaloSimulation.h"
#include "ShowerConstants.h"

#include "TH1F.h"
#include "TH2F.h"
#include "TCanvas.h"

void ana_simu(Event& event)
{
    // Get calorimeter data from event.
    CaloSimulation::CalData calData = event.calData();

    // List of layer energies
    float layerEnergies[CalConst::NbLayers] = {0.};
    // 2D array of XY energies
    float XYEnergies[CalConst::NbCellsInXY][CalConst::NbCellsInXY] = {0.};

    for (auto const& it: calData){ // iterate over caldata map
        auto cellAddress = it.first;  // get cell adresses (keys of the map)
        auto cell        = it.second; // get cells (values of the map)

        int currentLayer = cellAddress.layer(); // Get layer of current cell
        int currentix    = cellAddress.ix();    // Get ix of current cell
        int currentiy    = cellAddress.iy();    // Get iy of current cell
        layerEnergies[currentLayer] += cell.energy(); // Add energy of current
                                                      // cell to the layer
        XYEnergies[currentix][currentiy] += cell.energy();
    }

    TH1F* histZ = new TH1F(Form("histZ_%i", event.eventNumber()),
                           "Longitudinal energy loss",
                           CalConst::NbLayers, 0, CalConst::NbLayers);
    for (size_t i = 0; i < sizeof(layerEnergies)/sizeof(layerEnergies[0]); i++){
        histZ->SetBinContent(i+1, layerEnergies[i]);
    }

    TH2F* histXY = new TH2F(Form("histXY_%i", event.eventNumber()),
                            "Transversal energy loss",
                            CalConst::NbCellsInXY, 0, CalConst::NbCellsInXY,
                            CalConst::NbCellsInXY, 0, CalConst::NbCellsInXY);

    for (size_t ix = 0; ix < CalConst::NbCellsInXY; ix++) {
        for (size_t iy = 0; iy < CalConst::NbCellsInXY; iy++) {
            histXY->SetBinContent(ix+1, iy+1, XYEnergies[ix][iy]);
        }
    }

    event.setHistXY(histXY);
    event.setHistZ(histZ);
}
