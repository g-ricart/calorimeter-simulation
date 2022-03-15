#include "../CellAddress.h"
#include "../CaloCell.h"
#include "../CaloGeometry.h"

// Check CellAddress implementation
CellAddress cell = CellAddress(40, 4, 0);
cout << "(" << cell.ix() << ", " << cell.iy() << ", " << cell.layer() << ")" << endl;
cout << cell.IsValid() << endl;

// Check CaloCell implementation
CaloCell cell_e = CaloCell(cell, 0.3);
cout << "energy = " << cell_e.energy() << endl;
cout << "address = " << cell_e.address() << endl;

// Check CaloGeometry implementation
CaloGeometry caloGeo = CaloGeometry();
cout << caloGeo.IsInside([0., 0., 0.], cell) << endl;
cout << "Center of cell : (" << caloGeo.xCentre(cell) << ", "
                             << caloGeo.yCentre(cell) << ", "
                             << caloGeo.zCentre(cell) << ")" << endl;
