#ifndef CaloGeometry_h
#define CaloGeometry_h

/**
 * CaloGeometry
 * Helpers to describe the geometry of the detector.
 */

#include "CaloConstants.h"
#include "CellAddress.h"

class CaloGeometry
{
public:

    // Constructor
    CaloGeometry();

    // Destructor
    ~CaloGeometry();

    // Return false if the (x,y,z) point is not located in the calorimeter
    // volume otherwise return true and fill the CellAddress variables with the
    // address of the cell that contains this point.
    static bool IsInside(double xyz[3], CellAddress& cellAddress);

    // Give the position of the cell center.
    static double xCentre(const CellAddress& cellAddress);
    static double yCentre(const CellAddress& cellAddress);
    static double zCentre(const CellAddress& cellAddress);

    // Give the list of centers.
    void xCenters(float*     xCenterArray);
    void yCenters(float*     yCenterArray);
    void layerCenters(float* layerCentersArray);

private:

};

#endif
