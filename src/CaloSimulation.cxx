#include "CaloSimulation.h"

//______________________________________________________________________________
CaloSimulation::CaloSimulation()
{
}

//______________________________________________________________________________
CaloSimulation::~CaloSimulation()
{
}

//______________________________________________________________________________
void CaloSimulation::CalorimeterData(CalData& caldata)
{
    for (size_t layer = 0; layer < CalConst::NbLayers; layer++) {
        for (size_t iy = 0; iy < CalConst::NbCellsInXY; iy++) {
            for (size_t ix = 0; ix < CalConst::NbCellsInXY; ix++) {

                CellAddress cellAddress = CellAddress(ix, iy, layer);
                CaloCell cell = CaloCell(cellAddress, 0.);

                caldata[cellAddress] = cell;
            }
        }
    }

    m_caldata = caldata;
}

//______________________________________________________________________________
void CaloSimulation::SimulateShower(float x, float y, float energy)
{

}
