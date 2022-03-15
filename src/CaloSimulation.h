#ifndef CaloSimulation_h
#define CaloSimulation_h

/**
 * CaloSimulation
 * Implements the simulation of the calorimter.
 */

#include "CellAddress.h"
#include "CaloCell.h"
#include "CaloConstants.h"
#include <vector>
#include <map>

class CaloSimulation
{

public:

    typedef std::map<CellAddress, CaloCell> CalData;

    // Constructor
	CaloSimulation();

    //Destructor
    ~CaloSimulation();

	// Add the calorimeter cells to the vector of cell caldata.
	// TODO: to be implemented.
	void CalorimeterData(CalData& caldata);

	// Simulate a shower of a given energy, starting from the impact point (x,y)
	// of the electron at the front end of the calorimeter.
	// TODO: to be implemented.
	void SimulateShower(float x, float y, float energy);

	// Print all the cells.
	friend std::ostream& operator<<(std::ostream& os, const CaloSimulation& cs)
    {
        for (auto const& x: cs.m_caldata) {
            os << x.first << ": " << x.second;
            os << "\n";
        }
        return os;
    }

private: // TODO: to be completed.
    CalData m_caldata;

};

#endif
