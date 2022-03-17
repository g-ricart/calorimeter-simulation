#include "CaloGeometry.h"

//______________________________________________________________________________
CaloGeometry::CaloGeometry()
{
}

//______________________________________________________________________________
CaloGeometry::~CaloGeometry()
{
}

//______________________________________________________________________________
bool CaloGeometry::IsInside(double xyz[3], CellAddress& cellAddress)
{
    // Cell position corresponding to xyz
    int ix     = int((xyz[0] - CalConst::XYMin)/CalConst::XYSize);
    int iy     = int((xyz[1] - CalConst::XYMin)/CalConst::XYSize);
    int layer  = int((xyz[2] - CalConst::ZMin)/CalConst::ZSize);

    // Set cell coordinates
    cellAddress.setix(ix);
    cellAddress.setiy(iy);
    cellAddress.setlayer(layer);

    return (cellAddress.IsValid());
}

//______________________________________________________________________________
double CaloGeometry::xCentre(const CellAddress& cellAddress)
{
    return double(cellAddress.ix() + 0.5)*CalConst::XYSize + CalConst::XYMin;
}

//______________________________________________________________________________
double CaloGeometry::yCentre(const CellAddress& cellAddress)
{
    return double(cellAddress.iy() + 0.5)*CalConst::XYSize + CalConst::XYMin;
}

//______________________________________________________________________________
double CaloGeometry::zCentre(const CellAddress& cellAddress)
{
    return double(cellAddress.layer() + 0.5)*CalConst::ZSize + CalConst::ZMin;
}

//______________________________________________________________________________
void xCenters(float* xCenterArray)
{

}

//______________________________________________________________________________
void yCenters(float* yCenterArray)
{

}

//______________________________________________________________________________
void layerCenters(float* layerCentersArray)
{

}
