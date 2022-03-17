#ifndef CaloConstants_h
#define CaloConstants_h

/**
 * CaloConstants
 * Defines constants used across many files of the project.
 */

 //! Dimensions of the calorimeter, in meters.
 /*! The front face of the
     calorimeter is set to be the xy plane. We assume that it is a square
     and the z axis represents the depth. */

namespace CalConst {

    static const float ZMin  = 0.; /*!< minimal value of z axis */
    static const float ZMax  = 1.; /*!< maximal value of z axis */
    static const float XYMin = -2.; /*!< minimal value of x and y axis */
    static const float XYMax = 2.; /*!< maximal value of x and y axis */

    static const int NbCellsInXY = 40; /*!< number of cells in x (or y) direction */
    static const int NbLayers    = 10; /*!< number of layers in z direction */

    static const float XYSize = (XYMax - XYMin) / NbCellsInXY;/*!< Cell size in x-y*/
    static const float ZSize  = (ZMax - ZMin) / NbLayers;/*!< Cell size in x-y*/
}

#endif
