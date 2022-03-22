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

    // Fit parameters of S-Shape (s0 + s1*x + s2*x**2 + s3*x**3) in x and y
    static const float s0X = -1.46517e-05;
    static const float s1X = -0.0555484;
    static const float s2X = 1.67576;
    static const float s3X = -11.1799;

    static const float s0Y = 1.22767e-06;
    static const float s1Y = -0.0561498;
    static const float s2Y = 1.68108;
    static const float s3Y = -11.183;

    // Fit paramaeters of S-Shape (p0*sin(p1*x + p2))
    static const float p0X = 0.000549641;
    static const float p1X = 58.9337;
    static const float p2X = -2.94605;

    static const float p0Y = 0.000549483;
    static const float p1Y = 59.1057;
    static const float p2Y = -2.96516;
}

#endif
