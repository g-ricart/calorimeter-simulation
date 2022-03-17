#include <cmath>

#include "TRandom3.h"
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
void reconstruct(Event& event, CaloSimulation& caloSim)
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
}
