void plot(){

TFile* f1 = TFile::Open("prunedmass_cv.root");
TFile* f2 = TFile::Open("prunedmass_up.root");
TFile* f3 = TFile::Open("prunedmass_down.root");

TH1F* cv = (TH1F*)f1->Get("AK8jetPrunedMass");
TH1F* up = (TH1F*)f2->Get("AK8jetPrunedMass");
TH1F* down = (TH1F*)f3->Get("AK8jetPrunedMass");

TLegend* l = new TLegend(0.6645729,0.701049,0.8743719,0.8706294,"","NDC");
l->SetLineWidth(2);
l->SetBorderSize(0);
l->SetFillColor(0);
l->SetFillStyle(0);
l->SetTextFont(42);
l->SetTextSize(0.035);
l->SetTextAlign(12);

cv->SetLineColor(kRed);
cv->SetLineWidth(2);
up->SetLineColor(kBlack);
up->SetFillColor(kBlack);
up->SetFillStyle(3018);
down->SetLineColor(kBlue);
down->SetFillColor(kBlue);

l->AddEntry(cv,"central value","L");
l->AddEntry(up,"scale up","F");
l->AddEntry(down,"scale down","F");

down->Draw("HIST");
cv->Draw("HISTsame");
up->Draw("HISTsame");
l->Draw();

}
