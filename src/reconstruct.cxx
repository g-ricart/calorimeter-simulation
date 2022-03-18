#include <cmath>

#include "TRandom3.h"
#include "TGraph.h"
#include "TF1.h"

#include "ShowerConstants.h"
#include "Event.h"
#include "CaloSimulation.h"
#include "CaloCell.h"
#include "CellAddress.h"

using namespace std;

/**
 * @brief This function generates the reconstructed impact point.
 * @param[in] event Event object.
 */
void reconstruct(Event& event, CaloSimulation& caloSim,
                float* xCenterArray,
                float* yCenterArray,
                float* layerCenterArray)
{
    CaloSimulation::CalData calData = caloSim.GetCalData();

    CellAddress currentAddress;
    CaloCell    currentCell;

    // List to store energies
    float layerEnergies[CalConst::NbLayers] = {0.}; // List of layer energies
    float xEnergies[CalConst::NbCellsInXY]  = {0.}; // List of energies along X
    float yEnergies[CalConst::NbCellsInXY]  = {0.}; // List of energies along Y

    for (auto& it: calData) {
        currentAddress = it.first;
        currentCell    = it.second;

        float layer  = currentAddress.layer();
        float ix     = currentAddress.ix();
        float iy     = currentAddress.iy();
        float energy = currentAddress.energyMeas()

        layerEnergies[layer] += energy;
        xEnergies[ix]        += energy;
        yEnergies[iy]        += energy;
    }

    // TGraphs to fit X and Y energies
    TGraph* graphX = new TGraph(CalConst::NbCellsInXY, xCenterArray, xEnergies);
    TGraph* graphY = new TGraph(CalConst::NbCellsInXY, yCenterArray, yEnergies);

    TF1* gausFit = new TF1("gausFit", "gaus(0)", CalConst::XYMin,
                                                 CalConst::XYMax);
    gausFit->SetParName(0, "const");
    gausFit->SetParName(1, "mean");
    gausFit->SetParName(2, "sigma");

}
