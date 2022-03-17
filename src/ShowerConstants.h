#ifndef ShowerConstants_h
#define ShowerConstants_h

/**
 * ShowerConstants
 * Defines constants for the shower simulation
 */

    //! Initial energy of the particle e0.
    //! Radiation length x0.
    //! Variables of the dEdt fonction a and b.
    //! Moliere radius of the shower molRad.

namespace ShowConst {
    static const float e0     = 50;
    static const float x0     = 1e-2;
    static const float a      = 4.;
    static const float b      = .5;
    static const float molRad = 5e-2;

    static const float impactXMin = CalConst::XYMin;
    static const float impactXMax = CalConst::XYMax;
    static const float impactYMin = CalConst::XYMin;
    static const float impactYMax = CalConst::XYMax;
}

#endif
