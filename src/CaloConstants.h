#ifndef CaloConstants_h
#define CaloConstants_h

/**
 * CaloConstants
 * Defines constants used across many files of the project.
 */

 //! Dimensions of the calorimeter, in meters.
 //! Number of cells in the xy plane and number of layers.
 //! Size of the cells in x, y and z.
 /*! The front face of the calorimeter is set to be the xy plane.
     We assume that it is a square and the z axis represents the depth.
     */

namespace CalConst {

    // Dimensions of the calorimeter
    static const float ZMin  = 0.;
    static const float ZMax  = 1.;
    static const float XYMin = -2.;
    static const float XYMax = 2.;

    // Number of cells
    static const int NbCellsInXY = 40;
    static const int NbLayers    = 10;

    // Size of the cells
    static const float XYSize = (XYMax - XYMin) / NbCellsInXY;
    static const float ZSize  = (ZMax - ZMin) / NbLayers;
}

#endif
