#ifndef CaloSimulation_h
#define CaloSimulation_h

/**
 * \class CaloSimulation
 * Implements the simulation of the calorimter.
 */

#include "CellAddress.h"
#include "CaloCell.h"
#include "CaloConstants.h"
#include "ShowerConstants.h"
#include "TRandom3.h"

#include "TF1.h"
#include "TF2.h"
#include "TMath.h"

#include <vector>
#include <map>

class CaloSimulation
{

public:

    /*!
        \typedef CalData
        Defines a type allowing to store calorimeter data.
        Map with keys being of type CellAddress and values of type CaloCell
        \sa CellAddress
        \sa CaloCell
    */
    typedef std::map<CellAddress, CaloCell> CalData;

    //! Constructor
    CaloSimulation();

    //! Destructor
    ~CaloSimulation();

    //! Add the calorimeter cells to the map of cell caldata.
    void CalorimeterData();

    /*! Simulate a shower of a given energy, starting from the impact point (x,y)
        of the electron at the front end of the calorimeter.
        \param x float: position of impact point on x axis
        \param y float: position of impact point on y axis
        \param energy float: initial energy of the particle
    */
    void SimulateShower(float x, float y, float energy);

    // CAN DO: creat layer class including all cells of the same layer in a map
    // iterate over each layer to get map + layer energy
    // iterate over each cell of the map and compute cell energy

    //! Set all cell energy and total energy to zero.
    void Reset();

    /*!
        \class FunctionObjectdEdz
        Longitudinal deposited energy function
    */
    class FunctionObjectdEdz
    {
    public:
        //! Definition of the operator allowing to call the object
        Double_t operator()(Double_t *x, Double_t *p);
    };

    /*!
        \class FunctionObjectdEdz
        Transverse deposited energy function
    */
    class FunctionObjectdETrans
    {
    public:
        //! Definition of the operator allowing to call the object
        Double_t operator()(Double_t *x, Double_t *p);
    };

    //! Get the calorimeter data caldata (type CalData)
    CalData GetCalData()  { return m_caldata;  }
    //! Get the total true energy deposited in the calorimeter (type float)
    float   GeteTrueTot() { return m_eTrueTot; }
    //! Get the total measured energy deposited in the calorimeter (type float)
    float   GeteMeasTot() { return m_eMeasTot; }

    //!"Print" function for CaloSimulation
    friend std::ostream& operator<<(std::ostream& os, const CaloSimulation& cs)
    {
        for (auto const& x: cs.m_caldata) {
            os << x.first << ": " << x.second;
            os << "\n";
        }
        return os;
    }

private:
    CalData m_caldata;
    float   m_eTrueTot; // total true energy
    float   m_eMeasTot; // total measured energy

};

#endif
