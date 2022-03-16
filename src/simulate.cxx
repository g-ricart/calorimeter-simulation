#include "Event.h"
#include "CaloSimulation.h"
#include "ShowerConstants.h"

#include "TRandom.h"

void simulate(Event& event)
{
    // simulate the event
    event.seteTrue(ShowConst::e0); // fixed true energy

    // Build calorimeter
    // CAN DO: Add a caloReset method to empty all cells and define only one
    // calorimeter for all the events.
    CaloSimulation caloSim;
    caloSim.CalorimeterData();

    // Draw random point on calorimeter surface.
    float x = gRandom->Uniform(abs(CalConst::XYMin - CalConst::XYMax))
           + CalConst::XYMin;
    float y = gRandom->Uniform(abs(CalConst::XYMin - CalConst::XYMax))
           + CalConst::XYMin;

    float impactPoint[2] = {x, y};

    // Simulate the shower
    caloSim.SimulateShower(x, y, ShowConst::e0);
    CaloSimulation::CalData calData = caloSim.GetCalData();

    // Store variables in event
    event.setImpactPoint(impactPoint);
    event.setCalData(calData);
}
