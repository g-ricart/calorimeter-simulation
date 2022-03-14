#include <cmath>
#include "TRandom3.h"

#include "Event.h"

using namespace std;

/**
 * @brief This function generates the reconstrcuted parameters.
 * @details The reconstructed energy `eReco` is obtained by smearing the true value `eTrue`.
 * A random generator is used to draw a random value with +/- 0.5 GeV areound the true value.
 * @param[in] event Event object.
 */
void reconstruct(Event& event)
{
    TRandom3 *rand = new TRandom3(0);
    rand->SetSeed(0);
    Float_t e = event.eTrue(); // get true energy
    Float_t eReso = 0.1 * sqrt(e); // compute resolution
    Float_t eSmeared = e + rand->Gaus(0, eReso); // smear with a gaussian distribution
    Float_t eBias = eSmeared + 0.1; // introduce bias
    event.seteReco(eSmeared); // set the reconstructed energy
    event.seteRecoBias(eBias); // set biased reconstructed energy 
    delete rand;
}
