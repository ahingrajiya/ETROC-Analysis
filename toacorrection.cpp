void toacorrection()
{
    TFile *f1 = TFile::Open("build/oReadEtroc2.root");
    TProfile *board0 = (TProfile *)f1->Get("pActualDTOAvsActualTOT_0");
    // board0->Draw();

    TF1 *f = new TF1("f", "pol8", 0.0, 6.2);
    board0->Fit("f", "", "", 1.1, 6.2);
    // toa->Draw();
    // totvstoa0->Draw("COLZ");

    // TF1 *gauss = new TF1("gauss", "gaus", 40.0, 160.0);

    // TH1D *h3 = (TH1D *)f1->Get("h3");
    // h3->Fit("gaus", "", "", -44, 36);

    // TH1D *h4 = (TH1D *)f1->Get("h4");
    // h4->Fit("gaus", "", "", -44, 36);

    // TH1D *h5 = (TH1D *)f1->Get("h5");
    // h5->Fit("gaus", "", "", -45, 45);

    // TH1D *h6 = (TH1D *)f1->Get("h6");
    // h6->Fit("gaus", "", "", -60, 60);
}