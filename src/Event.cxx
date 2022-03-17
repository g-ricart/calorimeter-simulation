// TODO: To be completed.

#include "Event.h"

//______________________________________________________________________________
Event::Event()
{
}

//______________________________________________________________________________
Event::~Event()
{
}

//______________________________________________________________________________
void Event::build(int eventNumber)
{
    // set event number
    m_eventNumber = eventNumber;

    // initialize data member to invalid values
    m_eTrue       = -999.;
    m_eReco       = -999.;
    m_eRecoBias   = -999.;
    m_xReco       = -999.;
    m_yReco       = -999.;
}

//______________________________________________________________________________
void Event::setImpactPoint(float xy[2])
{
    for (size_t i = 0; i < sizeof(xy)/sizeof(xy[0]); i++) {
        m_impactPoint[i] = xy[i];
    }
}
