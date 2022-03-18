#ifndef CaloCell_h
#define CaloCell_h

/**
 * \class CaloCell
 * Reprensents a cell of the calorimeter, and its energy.
 */

#include "CellAddress.h"

class CaloCell
{
public:

    //! Default constructor needed of containers of the standard template library.
    CaloCell();

    //! Full constructor.
    /*!
        \param ca object of type CellAddress
        \param energy float : energy in the cell
        \sa CellAddress
    */
    CaloCell(const CellAddress& ca, float energyTrue, float energyMeas);

    //! Destructor.
    ~CaloCell();

    //! Access true energy of the cell.
    float energyTrue() const { return m_energyTrue; }
    //! Access measured energy of the cell.
    float energyMeas() const { return m_energyMeas; }
    //! Access address of the cell.
    CellAddress address() const { return m_address; }

    //! Set true energy of the cell.
    void setEnergyTrue(float energyTrue) { m_energyTrue = energyTrue; }
    //! Set measured energy of the cell.
    void setEnergyMeas(float energyMeas) { m_energyMeas = energyMeas; }

    /*!
        "Print" function for CaloCell.
        \sa CaloCell(const CellAddress& ca, float energy)
    */
    friend std::ostream& operator<<(std::ostream& os, const CaloCell& y)
    {
        os << "[" << y.address() << ", " << y.energyTrue() << ", " << y.energyMeas() << "]";
        return os;
    }

private:
    float       m_energyTrue; // True enregy of the cell
    float       m_energyMeas; // True energy smeared with a gaussian
    CellAddress m_address;

};

#endif
