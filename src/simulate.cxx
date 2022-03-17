#include "Event.h"
#include "CaloSimulation.h"
#include "ShowerConstants.h"

#include "TRandom.h"

void simulate(Event& event, CaloSimulation& caloSim)
{
    // simulate the event
    event.seteTrue(ShowConst::e0); // fixed true energy

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

    // Store variables in event
    event.setxTrue(x);
    event.setyTrue(y);
    event.setCalData(calData);
}
