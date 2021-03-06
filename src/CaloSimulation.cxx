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
                CaloCell cell = CaloCell(cellAddress, 0., 0.);

                m_caldata[cellAddress] = cell;
            }
        }
    }
}

//______________________________________________________________________________
void CaloSimulation::SimulateShower(float xImpact, float yImpact, float energy)
{
    TRandom3 *rand = new TRandom3(0);

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
                float cellEnergyTrue = cellEnergyRatio*layerEnergy;

                // Smear true energy value by a gaussian to emulate calo response
                float eReso = 0.1 * sqrt(cellEnergyTrue/ShowConst::e0);
                float cellEnergyMeas = cellEnergyTrue + rand->Gaus(0, eReso);

                CellAddress cellAddress = CellAddress(ix, iy, layer);
                m_caldata[cellAddress].setEnergyTrue(cellEnergyTrue);
                m_caldata[cellAddress].setEnergyMeas(cellEnergyMeas);

                m_eTrueTot += cellEnergyTrue;
                m_eMeasTot += cellEnergyMeas;
            }
        }
    }
}

//______________________________________________________________________________
void CaloSimulation::Reset()
{
    for (auto& it: m_caldata) {
        it.second.setEnergyTrue(0.);
        it.second.setEnergyMeas(0.);
    }

    m_eTrueTot = 0.;
    m_eMeasTot = 0.;
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
