#include <cmath>

#include "TRandom3.h"
#include "TF1.h"

#include "Event.h"
#include "ShowerConstants.h"
#include "CaloSimulation.h"

using namespace std;

/**
 * @brief This function generates the reconstructed impact point.
 * @param[in] event Event object.
 */
void reconstruct(Event& event, CaloSimulation& caloSim)
{
    CaloSimulation::CalData calData = caloSim.GetCalData();
}
