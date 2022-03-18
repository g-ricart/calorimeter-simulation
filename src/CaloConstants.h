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
 //! Threshold energy deposited in a layer to reconstruct its impact point.

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

    // Layer threshold energy to reconstruct impact point
    static const float layerEnrThr = 1e-6;

    // Fit parameters of S-Shape (s0 + s1*x + s2*x**2 + s3*x**3)
    static const float s0 = 1.76793e-06;
    static const float s1 = -0.0564493;
    static const float s2 = -1.6935;
    static const float s3 = -11.2874;
}

#endif
