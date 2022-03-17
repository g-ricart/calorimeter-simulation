#include "CaloCell.h"

//______________________________________________________________________________
CaloCell::CaloCell()
{
}

//______________________________________________________________________________
CaloCell::CaloCell(const CellAddress& ca, float energyTrue, float energyMeas)
{
    m_energyTrue = energyTrue;
    m_energyMeas = energyMeas;
    m_address    = ca;
}

//______________________________________________________________________________
CaloCell::~CaloCell()
{
}
