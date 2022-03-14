#include "TH1F.h"
#include "TRandom.h"

void genGauss()
{
    TH1F* h = new TH1F("hGauss", "Gaussian distribution", 100, -2., 2.);
    TF1* gaus = new TF1("gaus", "gaus", -2., 2.);

    // Draw 10000 numbers according the gaussian law
    // We use gRandom->Uniform(MAX)  to draw numbers
    // uniformly  between  0. and MAX
    for (Int_t i=0; i<10000; i++) {
        Float_t x = gRandom->Uniform(4.) - 2.;
        Float_t y = gRandom->Uniform(gaus->Eval(0));

        if (y <= gaus->Eval(x)) {
            h->Fill(x);
        }
    h->Draw();
    }
}
