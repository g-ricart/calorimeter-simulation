#ifndef CaloCell_h
#define CaloCell_h

/**
 * CaloCell
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
        \sa CellAddress()
    */
    CaloCell(const CellAddress& ca, float energy);

    //! Destructor.
    ~CaloCell();

    //! Access energy of the cell
    float energy() const;
    //! Acess address of the cell
    CellAddress address() const;

    //! Set energy of the cell
    void setEnergy(float energy);

    //! "Print" function for CaloCell.
    /*!
        \sa CaloCell(const CellAddress& ca, float energy)
    */
    friend std::ostream& operator<<(std::ostream& os, const CaloCell& y)
    {
        os << "[" << y.address() << ", " << y.energy() << "]";
        return os;
    }

private:
    float m_energy;
    CellAddress m_address;

};

#endif
