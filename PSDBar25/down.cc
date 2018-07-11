   
   cutg = new TCutG("CUTG",5);
   cutg->SetVarX("energy3");
   cutg->SetVarY("(energy1+0.01)/energy3");
   cutg->SetTitle("Graph");
   cutg->SetFillStyle(1000);
   cutg->SetPoint(0,2047.71,0.746862);
   cutg->SetPoint(1,3129.56,0.745597);
   cutg->SetPoint(2,3129.56,0.682338);
   cutg->SetPoint(3,2073.77,0.679808);
   cutg->SetPoint(4,2047.71,0.746862);
   cutg->Draw("cc");
