#include "CaloCell.h"

//______________________________________________________________________________
CaloCell::CaloCell()
{
}

//______________________________________________________________________________
CaloCell::CaloCell(const CellAddress& ca, float energy)
{
    m_energy    = energy;
    m_address   = ca;
}

//______________________________________________________________________________
CaloCell::~CaloCell()
{
}


//______________________________________________________________________________
float CaloCell::energy() const
{
    return m_energy;
}

//______________________________________________________________________________
CellAddress CaloCell::address() const
{
    return m_address;
}

//______________________________________________________________________________
void CaloCell::setEnergy(float energy)
{
    m_energy = energy;
}
