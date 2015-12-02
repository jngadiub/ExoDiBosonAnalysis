void PUmacro(){

TString fname = "../data/biasXsec_72000.root";
TFile* f = TFile::Open(fname);
TH1F* hdata = (TH1F*)f->Get("pileup");
hdata->Scale(1./hdata->Integral());

double npu2015_25ns[52] = {
     4.8551E-07,
     1.74806E-06,
     3.30868E-06,
     1.62972E-05,
     4.95667E-05,
     0.000606966,
     0.003307249,
     0.010340741,
     0.022852296,
     0.041948781,
     0.058609363,
     0.067475755,
     0.072817826,
     0.075931405,
     0.076782504,
     0.076202319,
     0.074502547,
     0.072355135,
     0.069642102,
     0.064920999,
     0.05725576,
     0.047289348,
     0.036528446,
     0.026376131,
     0.017806872,
     0.011249422,
     0.006643385,
     0.003662904,
     0.001899681,
     0.00095614,
     0.00050028,
     0.000297353,
     0.000208717,
     0.000165856,
     0.000139974,
     0.000120481,
     0.000103826,
     8.88868E-05,
     7.53323E-05,
     6.30863E-05,
     5.21356E-05,
     4.24754E-05,
     3.40876E-05,
     2.69282E-05,
     2.09267E-05,
     1.5989E-05,
     4.8551E-06,
     2.42755E-06,
     4.8551E-07,
     2.42755E-07,
     1.21378E-07,
     4.8551E-08};

TH1F* hmc = new TH1F("hmc","hmc",52,0,52);
for( int i = 0; i < 52; i++ ){
 hmc->SetBinContent(i+1,npu2015_25ns[i]);
}

fname = "../../AnalysisOutput/WJets.PU.root";
TFile* f1 = TFile::Open(fname);
TH1F* hnPVs = (TH1F*)f1->Get("nVertices");
hnPVs->Scale(1./hnPVs->Integral());
hnPVs->SetLineColor(kSpring-1);
hnPVs->SetLineWidth(2);
hnPVs->SetMaximum(0.25);
hnPVs->Draw("HIST");
hnPVs->SaveAs("pumc.root");

TH1F* hPUtrue = (TH1F*)f1->Get("nPUTrue");
hPUtrue->Scale(1./hPUtrue->Integral());
hPUtrue->SetLineColor(kBlue);
hPUtrue->SetLineWidth(2);
//hPUtrue->Draw("sameHIST");

//TH1F* hPUw = (TH1F*)f1->Get("PUWeights");
//hPUw->Scale(1./hPUw->Integral());
//hPUw->SetLineColor(kOrange);
//hPUw->SetLineWidth(2);
//hPUw->Draw("sameHIST");

hmc->SetLineColor(kRed);
//hmc->SetMarkerStyle(20);
hmc->SetMarkerColor(kRed);
hmc->SetLineWidth(2);
//hdata->Draw();
hmc->Draw("sameHIST");

fname = "../../AnalysisOutput/SingleMuon.PU.root";
TFile* f2 = TFile::Open(fname);
TH1F* hnPVs_data = (TH1F*)f2->Get("nVertices");
hnPVs_data->Scale(1./hnPVs_data->Integral());
hnPVs_data->SetLineColor(kBlack);
hnPVs_data->SetLineWidth(2);
hnPVs_data->SetMarkerStyle(20);
hnPVs_data->Draw("Psame");
hnPVs_data->SaveAs("pudata.root");

hdata->SetLineColor(kBlue);
hdata->SetLineWidth(2);
hdata->Draw("HISTsame");

TLegend* l = new TLegend(0.5028736,0.5254237,0.7025862,0.7733051,"","NDC");
l->SetLineWidth(2);
l->SetBorderSize(0);
l->SetFillColor(0);
l->SetTextFont(42);
l->SetTextSize(0.05);
l->SetTextAlign(12);

l->AddEntry(hmc,"25ns PU scenario","LP");
//l->AddEntry(hPUtrue,"number of PU true","L");
l->AddEntry(hnPVs,"number of PV (MC)","L");
l->AddEntry(hnPVs_data,"number of PV (data)","P");
l->AddEntry(hdata,"PU json file","L");

l->Draw();


for( int b = 1; b <= hdata->GetNbinsX(); b++ ){

 std::cout << "bin " << b << " npv " << hdata->GetBinCenter(b) << " data " << hdata->GetBinContent(b) << " mc " << hmc->GetBinContent(b);
 std::cout << " w " << (float)hdata->GetBinContent(b)/hmc->GetBinContent(b) << std::endl;

}

}
