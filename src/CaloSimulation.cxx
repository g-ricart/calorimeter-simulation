#include "CaloSimulation.h"

//______________________________________________________________________________
CaloSimulation::CaloSimulation()
{
}

//______________________________________________________________________________
CaloSimulation::~CaloSimulation()
{
}

//______________________________________________________________________________
void CaloSimulation::CalorimeterData()
{
    for (size_t layer = 0; layer < CalConst::NbLayers; layer++) {
        for (size_t iy = 0; iy < CalConst::NbCellsInXY; iy++) {
            for (size_t ix = 0; ix < CalConst::NbCellsInXY; ix++) {

                CellAddress cellAddress = CellAddress(ix, iy, layer);
                CaloCell cell = CaloCell(cellAddress, 0.);

                m_caldata[cellAddress] = cell;
            }
        }
    }
}

//______________________________________________________________________________
void CaloSimulation::SimulateShower(float xImpact, float yImpact, float energy)
{
    FunctionObjectdEdz fdEdz;
    TF1* dEdz = new TF1("dEdz", fdEdz, CalConst::ZMin, CalConst::ZMax, 1);
    dEdz->SetParName(0, "E0");
    dEdz->SetParameter("E0", energy);

    FunctionObjectdETrans fdETrans;
    TF2* dETrans = new TF2("dETrans",
                           fdETrans,
                           CalConst::XYMin,
                           CalConst::XYMax,
                           CalConst::XYMin,
                           CalConst::XYMax, 4);
    dETrans->SetParName(0, "xImpact");
    dETrans->SetParName(1, "xSigma");
    dETrans->SetParName(2, "yImpact");
    dETrans->SetParName(3, "ySigma");
    dETrans->SetParameter("xImpact", xImpact);
    dETrans->SetParameter("yImpact", yImpact);
    dETrans->SetParameter("xSigma", ShowConst::molRad);
    dETrans->SetParameter("ySigma", ShowConst::molRad);

    for (size_t layer = 0; layer < CalConst::NbLayers; layer++) {
        float z0 = layer*CalConst::ZSize - CalConst::ZMin;
        float z1 = (layer + 1)*CalConst::ZSize - CalConst::ZMin;
        float layerEnergy = dEdz->Integral(z0, z1);

        for (size_t iy = 0; iy < CalConst::NbCellsInXY; iy++) {
            for (size_t ix = 0; ix < CalConst::NbCellsInXY; ix++) {
                float x0 = float(ix)*CalConst::XYSize     + CalConst::XYMin;
                float x1 = float(ix + 1)*CalConst::XYSize + CalConst::XYMin;
                float y0 = float(iy)*CalConst::XYSize     + CalConst::XYMin;
                float y1 = float(iy + 1)*CalConst::XYSize + CalConst::XYMin;

                float cellEnergyRatio = dETrans->Integral(x0, x1, y0, y1);
                float cellEnergy = cellEnergyRatio*layerEnergy;

                CellAddress cellAddress = CellAddress(ix, iy, layer);
                m_caldata[cellAddress].setEnergy(cellEnergy);
            }
        }
    }
}

//______________________________________________________________________________
void CaloSimulation::Reset()
{
    for (auto const& it: m_caldata) {
        m_caldata[cellAddress].setEnergy(0);
    }
}


//______________________________________________________________________________
Double_t CaloSimulation::FunctionObjectdEdz::operator()(Double_t *x,
                                                        Double_t *par)
{
    Double_t z = x[0];
    Double_t dEdz = (par[0]/ShowConst::x0) * ShowConst::b;
    dEdz *= TMath::Power((ShowConst::b * z)/ShowConst::x0, ShowConst::a - 1.);
    dEdz *= TMath::Exp(-(ShowConst::b * z)/ShowConst::x0);
    dEdz /= TMath::Gamma(ShowConst::a);

    return dEdz;
}

//______________________________________________________________________________
Double_t CaloSimulation::FunctionObjectdETrans::operator()(Double_t *xy,
                                                           Double_t *par)
{
    Double_t x = xy[0];
    Double_t y = xy[1];

    Double_t dEdx = TMath::Gaus(x, par[0], par[1], true);
    Double_t dEdy = TMath::Gaus(y, par[2], par[3], true);

    return dEdx*dEdy;
}
