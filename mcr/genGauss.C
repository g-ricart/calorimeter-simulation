#include "TH1F.h"
#include "TRandom.h"

void genGauss()
{
    TH1F* h = new TH1F("hGauss", "Gaussian distribution", 100, -2., 2.);
    h->SetStats(0);
    TF1* gaus = new TF1("gaus", "gaus(0)", -2., 2.);
    gaus->SetParameters(1., 0., .5);

    // Draw 10000 numbers according the gaussian law
    // We use gRandom->Uniform(MAX)  to draw numbers
    // uniformly  between  0. and MAX

    Float_t x, y;
    for (Int_t i=0; i<10000; i++) {
        x = gRandom->Uniform(4.) - 2.;
        y = gRandom->Uniform(gaus->Eval(0));

        if (y <= gaus->Eval(x)) {
            h->Fill(x);
        }
    h->Draw();
    }
}
