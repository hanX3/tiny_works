
void test()
{
   TCanvas * CPol = new TCanvas("CPol","TGraphPolar Example",500,500);

   Double_t theta[16];
   Double_t radius[16];

   for (int i=0; i<16; i++) {
      theta[i]   = (i+1)*(TMath::Pi()/4.);
      radius[i]  = 100. + (i+1)*0.1/TMath::Pi();
   }

   TGraphPolar * grP1 = new TGraphPolar(16, theta, radius);
   grP1->SetTitle("");

   grP1->SetMarkerStyle(20);
   grP1->SetMarkerSize(2.);
   grP1->SetMarkerColor(4);
   grP1->SetLineColor(2);
   grP1->SetLineWidth(3);
   grP1->Draw("PE");

   CPol->Update();
   //grP1->GetPolargram()->SetToRadian();
}
