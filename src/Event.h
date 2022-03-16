#ifndef Event_h
#define Event_h

#include "CaloSimulation.h"
#include "TH1F.h"
#include "TH2F.h"

/**
 * @bried Event class.
 * @details This class describes an event.
 */
class Event {

private:
    int                     m_eventNumber ;   ///< event number.
    float                   m_eTrue ;         ///< true energy.
    float                   m_eReco ;         ///< reconstructed energy.
    float                   m_eRecoBias ;     ///< bias reconstruction energy.
    float                   m_impactPoint[2]; ///< impact point.
    CaloSimulation::CalData m_caldata;        ///< calorimeter data map.
    TH1F*                   m_histZ;          ///< layers energy histogram.
    TH2F*                   m_histXY;         ///< transverse energy histogram.


public:
    Event(); ///< Constructor.
    virtual ~Event(); ///< Destructor.

    void build(int eventNumber); // initialize

    // setters
    void setEventNumber(int eventNumber) { m_eventNumber = eventNumber; }
    void seteTrue(float eTrue) { m_eTrue = eTrue; }
    void seteReco(float eReco) { m_eReco = eReco; }
    void seteRecoBias(float eRecoBias) { m_eRecoBias = eRecoBias; }
    void setImpactPoint(float xy[2]);
    void setCalData(CaloSimulation::CalData caldata) { m_caldata = caldata; }
    void setHistZ(TH1F histZ) { m_histZ = histZ; }
    void setHistXY(TH2F histXY) { m_histXY = histXY; }

    // getters
    int    eventNumber()              const { return m_eventNumber; }
    float  eTrue()                    const { return m_eTrue; }
    float  eReco()                    const { return m_eReco; }
    float  eRecoBias()                const { return m_eRecoBias; }
    float* impactPoint()                    { return m_impactPoint; }
    CaloSimulation::CalData calData() const { return m_caldata; }
    TH1F*  histZ()                    const { return m_histZ; }
    TH2F*  histXY()                   const { return m_histXY; }
};

#endif
