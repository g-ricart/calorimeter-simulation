#include "CellAddress.h"

//______________________________________________________________________________
CellAddress::CellAddress()
{
}

//______________________________________________________________________________
CellAddress::CellAddress(int ix, int iy, int layer)
{
    m_ix    = ix;
    m_iy    = iy;
    m_layer = layer;
}

//______________________________________________________________________________
CellAddress::~CellAddress()
{
}

//______________________________________________________________________________
bool CellAddress::IsValid() const
{
    return(m_ix    < CalConst::NbCellsInXY && m_ix >= 0
        && m_iy    < CalConst::NbCellsInXY && m_iy >= 0
        && m_layer < CalConst::NbLayers && m_layer >= 0);
}

//______________________________________________________________________________
int CellAddress::ix() const
{
    return m_ix;
}

//______________________________________________________________________________
int CellAddress::iy() const
{
    return m_iy;
}

//______________________________________________________________________________
int CellAddress::layer() const
{
    return m_layer;
}
