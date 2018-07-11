   
   TCutG *cutg = new TCutG("CUTG",5);
   cutg->SetVarX("energy3");
   cutg->SetVarY("(energy1+0.01)/energy3");
   cutg->SetTitle("Graph");
   cutg->SetFillStyle(1000);
   cutg->SetPoint(0,1904.33,0.954352);
   cutg->SetPoint(1,1910.84,0.892358);
   cutg->SetPoint(2,2849.32,0.872115);
   cutg->SetPoint(3,2862.36,0.913866);
   cutg->SetPoint(4,1904.33,0.954352);
   cutg->Draw("cc");
