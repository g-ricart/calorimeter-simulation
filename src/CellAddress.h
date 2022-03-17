#ifndef CellAddress_h
#define CellAddress_h

/**
 * CellAddress
 * Implements a way to identify a calorimeter cell using its positions along
 * the x, y and z axis.
 */

#include <iostream>
#include "CaloConstants.h"

class CellAddress
{
public:
	//! Default constructor, gives you an invalid address.
	CellAddress();

	//! Full constructor.
	/*!
		\param ix integer: index of cell on x axis
		\param iy integer: index of cell on y axis
		\param layer integer: index of cell on z axis
	*/
	CellAddress(int ix, int iy, int layer);

  //! Destructor
  ~CellAddress();

	//!  Function to know if the address of a cell is in the calorimeter
	/*!
		\return True if the address is valid
	*/
	bool IsValid() const;

  //! Set cell index on x axis
  void setix(int ix) { m_ix = ix; }
	//! Set cell index on y axis
  void setiy(int iy) { m_iy = iy; }
	//! Set cell index on z axis
  void setlayer(int layer) { m_layer = layer; }

	//! Access cell index on x axis
	int ix() const;
	//! Access cell index on y axis
	int iy() const;
	//! Access cell index on z axis
	int layer() const;

	//! This defines comparator "<" between two CellAddress. This is necessary for
	//! some container types of the standard template library (std).
	/*!
		\param x : object of type const CellAddress
		\return bool : compares elements of CellAddress. First ix, then iy
										and then layer
		\sa CellAddress(int ix, int iy, int layer)

		///[Example]
		//Example of usage
		CellAddress cell1 = CellAddress(0, 5, 1);
		CellAddress cell2 = CellAddress(0, 4, 2);
		bool Test = cell2 < cell1;
		//Test will have value "True"
		///[Example]
	*/
	bool operator<(const CellAddress& x) const
	{
		if (x.m_iy == this ->m_iy && x.m_ix == this->m_ix)
		{
			return (this->m_layer < x.m_layer);
		}

		if (x.m_ix == this->m_ix)
		{
			return (this->m_iy < x.m_iy);
		}

		return (this->m_ix < x.m_ix);
	}

	//! This defines comparator ">" between two CellAddress. This is necessary for
	//! some container types of the standard template library (std).
	/*!
		\param x : object of type const CellAddress
		\return bool : compares elements of CellAddress. First ix, then iy
										and then layer
		\sa CellAddress(int ix, int iy, int layer)
		///[Example]
		//Example of usage
		CellAddress cell1 = CellAddress(0, 5, 2);
		CellAddress cell2 = CellAddress(0, 5, 4);
		bool Test = cell2 > cell1;
		//Test will have value "True"
		///[Example]
	*/

	bool operator>(const CellAddress& x) const
	{
		if (x.m_iy == this ->m_iy && x.m_ix == this->m_ix) return (this->m_layer > x.m_layer);
		if (x.m_ix == this->m_ix) return (this->m_iy > x.m_iy);
		return (this->m_ix > x.m_ix);
	}

	//! Display cell address content.
	/*!
		\sa CellAddress(int ix, int iy, int layer)
	*/
	friend std::ostream& operator<<(std::ostream& os, const CellAddress& y)
	{
		os << "(" << y.ix() << ", " << y.iy() << ", " << y.layer() << ")";
		return os;
	}

private:
	// declaration of private variables
	int m_ix;
	int m_iy;
	int m_layer;

};

#endif
