void plots()
{
    TFile *f1 = TFile::Open("build/oReadEtroc2Run20.root");
    TFile *f2 = TFile::Open("build/oReadEtroc2Run21.root");
    TFile *f3 = TFile::Open("build/oReadEtroc2Run24.root");
    TFile *f4 = TFile::Open("build/oReadEtroc2Run25.root");
    TFile *f5 = TFile::Open("build/oReadEtroc2Run26.root");
    TFile *f6 = TFile::Open("build/oReadEtroc2Run27.root");
    TFile *f7 = TFile::Open("build/oReadEtroc2Run31.root");
    TFile *f8 = TFile::Open("build/oReadEtroc2Run34.root");

    int DSL_colors[12] = {
        TColor::GetColor(0, 0, 0),
        TColor::GetColor(230, 0, 0),
        TColor::GetColor(0, 190, 0),
        TColor::GetColor(0, 200, 255),
        TColor::GetColor(150, 0, 0),
        TColor::GetColor(0, 100, 0),
        TColor::GetColor(0, 0, 200),
        TColor::GetColor(230, 180, 30),
        TColor::GetColor(250, 100, 0),
        TColor::GetColor(80, 80, 85),
        TColor::GetColor(85, 40, 80),
        TColor::GetColor(250, 20, 250)};

    TFile *files[8] = {f1, f2, f3, f4, f5, f6, f7, f8};
    TH1D *cal0[8];
    TH1D *cal1[8];

    gStyle->SetOptStat(0);
    for (Int_t i{0}; i < 8; i++)
    {
        cal0[i] = (TH1D *)files[i]->Get("hCAL_0");
        cal1[i] = (TH1D *)files[i]->Get("hCAL_1");
    }

    std::string legend_entry[] = {"Run20", "Run21", "Run24", "Run25", "Run26", "Run27", "Run31", "Run34"};
    // TLegend *legend = new TLegend(0.15, 0.5, 0.35, 0.8);
    // legend->SetBorderSize(0);
    // legend->SetTextSize(0.04);
    // legend->SetTextFont(42);
    // auto *c1 = new TCanvas("c1", "Board 0 CAL", 800, 800);

    // for (Int_t i{0}; i < 8; i++)
    // {
    //     cal0[i]->SetMarkerStyle(71 + i);
    //     cal0[i]->SetMarkerColor(DSL_colors[i]);
    //     cal0[i]->SetMarkerSize(1.85);
    //     legend->AddEntry(cal0[i], Form("%s", legend_entry[i].c_str()), "p");
    //     cal0[i]->Draw("SAME");
    // }
    // c1->Draw();

    // legend->Draw();
    // c1->Update();

    TLegend *legend1 = new TLegend(0.7, 0.4, 0.9, 0.8);
    legend1->SetBorderSize(0);
    legend1->SetTextSize(0.04);
    legend1->SetTextFont(42);
    auto *c2 = new TCanvas("c2", "Board 1 CAL", 800, 800);

    for (Int_t i{0}; i < 8; i++)
    {
        cal1[i]->SetMarkerStyle(71 + i);
        cal1[i]->SetMarkerColor(DSL_colors[i]);
        cal1[i]->SetMarkerSize(1.85);
        legend1->AddEntry(cal1[i], Form("%s", legend_entry[i].c_str()), "p");
        cal1[i]->Draw("SAME");
    }
    c2->Draw();
    legend1->Draw();
    c2->Update();
}