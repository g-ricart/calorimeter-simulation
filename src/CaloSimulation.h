#ifndef CaloSimulation_h
#define CaloSimulation_h

/**
 * CaloSimulation
 * Implements the simulation of the calorimter.
 */

#include "CellAddress.h"
#include "CaloCell.h"
#include "CaloConstants.h"
#include "ShowerConstants.h"

#include "TF1.h"
#include "TF2.h"
#include "TMath.h"

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

	// Add the calorimeter cells to the map of cell caldata.
	void CalorimeterData();

	// Simulate a shower of a given energy, starting from the impact point (x,y)
	// of the electron at the front end of the calorimeter.
    // CAN DO: creat layer class including all cells of the same layer in a map
    // iterate over each layer to get map + layer energy
    // iterate over each cell of the map and compute cell energy
	void SimulateShower(float x, float y, float energy);

    // Set all cell energy to zero.
    void Reset();

    // Longitudinal deposited energy function
    class FunctionObjectdEdz
    {
    public:
        Double_t operator()(Double_t *x, Double_t *p);
    };

    // Transverse deposited energy function
    class FunctionObjectdETrans
    {
    public:
        Double_t operator()(Double_t *x, Double_t *p);
    };

    // Getters
    CalData GetCalData() { return m_caldata; }

	// Print all the cells.
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

};

#endif
