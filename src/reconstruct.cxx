#include <cmath>
#include "TRandom3.h"

#include "Event.h"
#include "ShowerConstants.h"

using namespace std;

/**
 * @brief This function generates the reconstrcuted parameters.
 * @details The reconstructed energy `eReco` is obtained by smearing the true value `eTrue`.
 * A random generator is used to draw a random value with +/- 0.5 GeV areound the true value.
 * @param[in] event Event object.
 */
void reconstruct(Event& event)
{

}
