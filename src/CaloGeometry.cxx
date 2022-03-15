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
static bool IsInside(double xyz[3], CellAddress& cellAddress)
{
    // Cell position corresponding to xyz
    int ix     = floor((x[0] - CalConst::XYMin)/CalConst::XYSize);
    int iy     = floor((x[1] - CalConst::XYMin)/CalConst::XYSize);
    int ilayer = floor((x[3] - CalConst::ZMin)/CalConst::ZSize);

    if (cellAddress->IsValid()) {
        cellAddress->setix(ix);
        cellAddress->setiy(iy);
        cellAddress->ilayer(ilayer);

        return true;
    }

    return false;

}

//______________________________________________________________________________
static double xCentre(const CellAddress& cellAddress)
{

}

//______________________________________________________________________________
static double yCentre(const CellAddress& cellAddress)
