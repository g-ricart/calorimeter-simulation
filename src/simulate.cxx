#include "Event.h"
#include "CaloSimulation.h"
#include "ShowerConstants.h"

#include "TRandom.h"

void simulate(Event& event, CaloSimulation& caloSim)
{
    // simulate the event

    // Reset calorimeter
    caloSim.Reset();

    // Draw random point on calorimeter surface.
    float x = gRandom->Uniform(abs(ShowConst::impactXMin - ShowConst::impactXMax))
           + ShowConst::impactXMin;
    float y = gRandom->Uniform(abs(ShowConst::impactYMin - ShowConst::impactYMax))
           + ShowConst::impactYMin;

    // Simulate the shower
    caloSim.SimulateShower(x, y, ShowConst::e0);
    CaloSimulation::CalData calData = caloSim.GetCalData();

    // Get total measured energy.
    float eMeasTot = caloSim.GeteMeasTot();
    // Get total true energy.
    float eTrueTot = caloSim.GeteTrueTot();

    // Store variables in event
    event.setxTrue(x);
    event.setyTrue(y);
    event.setCalData(calData);
    event.seteTrue(eTrueTot);
    event.seteReco(eMeasTot);
}
