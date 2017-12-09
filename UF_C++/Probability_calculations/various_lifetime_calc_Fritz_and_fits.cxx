 /*
  //Here, calc lifetimes like Fritz does it??? We have average as "time_avg" and we calc. max value "time_max" above. Only for step 1 so far.   
  double tau_tot = 3.0*time_max; //static
  double tau_0 = time_avg; //static
  double tau_x = time_avg+0.9; //changing every iteration
  double tau_temp = 0;
  double precision = 0.001;
  double xx,zp1,zp2,xp1,xp2,xp3,z_tot,x_tot,dtau,atau,ptau; 
  ptau = 1.0;  

  while(ptau > precision){  
  xx = exp(tau_tot/tau_x);
  zp1 = (tau_x-tau_0)/tau_tot;
  zp2 = 1.0/(xx-1);
  xp1 = 1.0/tau_tot;
  xp2 = 1.0/(tau_x*tau_x);
  xp3 = xp2*xx*zp2*zp2;
  z_tot = zp1-zp2;
  x_tot = xp1-xp3;
  tau_temp = tau_x-z_tot/x_tot;
  dtau = tau_x-tau_temp;
  if(dtau >= 0) atau = dtau;
  else if(dtau < 0) atau = -dtau;
  else cout << "wtf?" << endl;
  ptau = atau/tau_x;
  cout << "0, x, temp, dtau, atau, ptau "  << tau_0 << " " << tau_x << " " << tau_temp << " " << dtau << " " << atau << " " <<ptau << endl;
  tau_x = tau_temp;
  }//end "while"
  cout << endl << "The halflife for the first step according Fritz's method is " << log(2)*tau_x << endl << endl;
  */


  /*
  //Fit functions to histograms
  //Histograms with logarithmic-sized bins
  //TF1 *pdf_logbins_1_test = new TF1("pdf_logbins_1_test","[1]*exp(log(x)+log(1/[0]))*exp(-exp(log(x)+log(1/[0])))",0.0001,1000);
  TF1 *pdf_logbins_1 = new TF1("pdf_logbins_1","[1]*x/[0]*exp(-x/[0])",exp(-5.75),exp(4.5)); //Equivalent to the one above
  pdf_logbins_1->SetParameter(0,halflife_ref[0]/log(2));
  pdf_logbins_1->SetParameter(1,exp(1));
  //h_decay_time_logbins[0]->Fit("pdf_logbins_1");
  cout << endl << "The halflife for the first step from fitting logbin-histograms is " << log(2)*(pdf_logbins_1->GetParameter(0)) << endl << endl;

  TF1 *pdf_logbins_2 = new TF1("pdf_logbins_2","[1]*x/[0]*exp(-x/[0])",exp(-5.75),exp(4.5)); //Equivalent to the one above
  pdf_logbins_2->SetParameter(0,halflife_ref[1]/log(2));
  pdf_logbins_2->SetParameter(1,exp(1));
  h_decay_time_logbins[1]->Fit("pdf_logbins_2");
  pdf_logbins_2->SetParameter(0,halflife_ref[1]/log(2));
  pdf_logbins_2->SetLineColor(5);
  pdf_logbins_2->Draw("same");

  TF1 *pdf_logbins_3 = new TF1("pdf_logbins_3","[1]*x/[0]*exp(-x/[0])",exp(-5.75),exp(4.5)); //Equivalent to the one above
  pdf_logbins_3->SetParameter(0,halflife_ref[2]/log(2));
  pdf_logbins_3->SetParameter(1,exp(1));
  h_decay_time_logbins[2]->Fit("pdf_logbins_3");
  pdf_logbins_3->SetParameter(0,halflife_ref[2]/log(2));
  pdf_logbins_3->SetLineColor(5);
  pdf_logbins_3->Draw("same");

  //Histograms containing the logarithms of the times
  TF1 *pdf_ln_1 = new TF1("pdf_ln_1","[1]*1/[0]*exp(-exp(x)/[0])*exp(x)",-6,4); 
  pdf_ln_1->SetParameter(0,halflife_ref_high[0]/log(2));
  pdf_ln_1->SetParameter(1,1);
  //h_decay_time_ln[0]->Fit("pdf_ln_1"); 
  cout << endl << "The halflife for the first step from fitting the logarithms of the times is " << log(2)*(pdf_ln_1->GetParameter(0))<< endl << endl;
  */
