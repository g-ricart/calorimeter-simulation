#include <cmath>

#include "TRandom3.h"
#include "TGraph.h"
#include "TF1.h"
#include "TMath.h"

#include "ShowerConstants.h"
#include "CaloConstants.h"
#include "Event.h"
#include "CaloSimulation.h"
#include "CaloCell.h"
#include "CellAddress.h"

using namespace std;

/**
 * @brief This function generates the reconstructed impact point.
 * @param[in] event Event object.
 */

float sShape(float x){
    return CalConst::s0 + CalConst::s1*x + CalConst::s2*pow(x, 2)
                                         + CalConst::s3*pow(x, 3);
}

void reconstruct(Event& event,
                 TF1*   fitFunc,
                 float* xCenterArray,
                 float* yCenterArray,
                 float* layerCenterArray)
{
    CaloSimulation::CalData calData = event.calData();

    CellAddress currentAddress;
    CaloCell    currentCell;

    // List to store energies
    float layerEnergies[CalConst::NbLayers] = {0.}; // List of layer energies
    float xEnergies[CalConst::NbCellsInXY]  = {0.}; // List of energies along X
    float yEnergies[CalConst::NbCellsInXY]  = {0.}; // List of energies along Y

    for (auto& it: calData) {
        currentAddress = it.first;
        currentCell    = it.second;

        int layer    = currentAddress.layer();
        int ix       = currentAddress.ix();
        int iy       = currentAddress.iy();
        float energy = currentCell.energyMeas();

        layerEnergies[layer] += energy;
        xEnergies[ix]        += energy;
        yEnergies[iy]        += energy;
    }

    float xReco = 0.;
    float yReco = 0.;

    // Gaussian fit of X and Y energy distributions for each layer above
    // threshold.
    // The maximum of the fit is taken as the reconstructed impact point.
    // A weighted mean on all reconstructed positions is computed to get the
    // final reconstructed impact x and y.

    for (size_t layer = 0; layer < CalConst::NbLayers; layer++) {

        float layerEnergy = layerEnergies[layer];

        if (layerEnergy >= CalConst::layerEnrThr) {

            // TGraphs to fit X and Y energies
            TGraph* graphX = new TGraph(CalConst::NbCellsInXY, xCenterArray, xEnergies);
            TGraph* graphY = new TGraph(CalConst::NbCellsInXY, yCenterArray, yEnergies);

            graphX->Fit(fitFunc, "Q");
            xReco += fitFunc->GetParameter(1)*layerEnergy;

            // cout << "xReco : " << xReco << " ; " << event.xTrue() << endl;
            // cout << "layerEnergy : " << layerEnergy << endl;

            graphY->Fit(fitFunc, "Q");
            yReco += fitFunc->GetParameter(1)*layerEnergy;

            // cout << "yReco : " << yReco << " ; " << event.yTrue() << endl;
        }

    }
    xReco /= event.eReco();
    yReco /= event.eReco();

    xReco += sShape(int((xReco - CalConst::XYMin)/CalConst::XYSize)
                                        *CalConst::XYSize/2. + CalConst::XYMin);
    yReco += sShape(int((yReco - CalConst::XYMin)/CalConst::XYSize)
                                        *CalConst::XYSize/2. + CalConst::XYMin);

    event.setxReco(xReco);
    event.setyReco(yReco);

    // cout << "xReco : " << xReco;
    // cout << "; xTrue : " << event.xTrue() << endl;
}
