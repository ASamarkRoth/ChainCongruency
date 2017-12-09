  double binstart[nr_of_logbins];
  double weight;


  //Construct logarithmic bins
  for(Int_t i = 0; i < nr_of_logbins; i++){
    binstart[i] = exp(log_start+(i*log_step));
    //cout << "binstart " << binstart[i] << endl;
  }
  
  //Calculate weight of each bin
  for(Int_t i = 0; i < nr_of_logbins-1; i += 100){
    weight = 1.0/binstart[i]*(binstart[i+1]-binstart[i]);
    //cout << "weight is" << weight << endl;
  }


  h_implant_energy = new TH1F("h_implant_energy","h_implant_energy",2000,0,20);
  
  h_decay_energy[0] = new TH1F("h_decay_energy[0]","h_decay_energy[0]",1200,0,12); 
  h_decay_energy[1] = new TH1F("h_decay_energy[1]","h_decay_energy[1]",1200,0,12); 
  h_decay_energy[2] = new TH1F("h_decay_energy[2]","h_decay_energy[2]",1200,0,12); 
  h_decay_energy[3] = new TH1F("h_decay_energy[3]","h_decay_energy[3]",1200,0,12); 
  h_decay_energy[4] = new TH1F("h_decay_energy[4]","h_decay_energy[4]",1200,0,12); 
  h_decay_energy[5] = new TH1F("h_decay_energy[5]","h_decay_energy[5]",1200,0,12); 
  h_decay_energy[6] = new TH1F("h_decay_energy[6]","h_decay_energy[6]",1200,0,12); 
  h_decay_energy[7] = new TH1F("h_decay_energy[7]","h_decay_energy[7]",1200,0,12); 
			
  h_decay_time_logbins[0] = new TH1F("h_decay_time_logbins[0]","h_decay_time_logbins[0]",nr_of_logbins,binstart); 
  h_decay_time_logbins[1] = new TH1F("h_decay_time_logbins[1]","h_decay_time_logbins[1]",nr_of_logbins,binstart); 
  h_decay_time_logbins[2] = new TH1F("h_decay_time_logbins[2]","h_decay_time_logbins[2]",nr_of_logbins,binstart); 
  h_decay_time_logbins[3] = new TH1F("h_decay_time_logbins[3]","h_decay_time_logbins[3]",nr_of_logbins,binstart); 
  h_decay_time_logbins[4] = new TH1F("h_decay_time_logbins[4]","h_decay_time_logbins[4]",nr_of_logbins,binstart); 
  h_decay_time_logbins[5] = new TH1F("h_decay_time_logbins[5]","h_decay_time_logbins[5]",nr_of_logbins,binstart); 
  h_decay_time_logbins[6] = new TH1F("h_decay_time_logbins[6]","h_decay_time_logbins[6]",nr_of_logbins,binstart); 
  h_decay_time_logbins[7] = new TH1F("h_decay_time_logbins[7]","h_decay_time_logbins[7]",nr_of_logbins,binstart); 

  h_decay_time[0] = new TH1F("h_decay_time[0]","h_decay_time[0]",10000,0,1111); 
  h_decay_time[1] = new TH1F("h_decay_time[1]","h_decay_time[1]",10000,0,1111); 
  h_decay_time[2] = new TH1F("h_decay_time[2]","h_decay_time[2]",10000,0,1111); 
  h_decay_time[3] = new TH1F("h_decay_time[3]","h_decay_time[3]",10000,0,1111);
  h_decay_time[4] = new TH1F("h_decay_time[4]","h_decay_time[4]",10000,0,1111);
  h_decay_time[5] = new TH1F("h_decay_time[5]","h_decay_time[5]",10000,0,1111);
  h_decay_time[6] = new TH1F("h_decay_time[6]","h_decay_time[6]",10000,0,1111);
  h_decay_time[7] = new TH1F("h_decay_time[7]","h_decay_time[7]",10000,0,1111);

  h_decay_time_ln[0] = new TH1F("h_decay_time_ln[0]","h_decay_time_ln[0]",100,-6,4); 
  h_decay_time_ln[1] = new TH1F("h_decay_time_ln[1]","h_decay_time_ln[1]",200,-5.5,5.5); 
  h_decay_time_ln[2] = new TH1F("h_decay_time_ln[2]","h_decay_time_ln[2]",200,-10,10); 
  h_decay_time_ln[3] = new TH1F("h_decay_time_ln[3]","h_decay_time_ln[3]",200,-10,10);
  h_decay_time_ln[4] = new TH1F("h_decay_time_ln[4]","h_decay_time_ln[4]",200,-10,10);
  h_decay_time_ln[5] = new TH1F("h_decay_time_ln[5]","h_decay_time_ln[5]",200,-10,10);
  h_decay_time_ln[6] = new TH1F("h_decay_time_ln[6]","h_decay_time_ln[6]",200,-10,10);
  h_decay_time_ln[7] = new TH1F("h_decay_time_ln[7]","h_decay_time_ln[7]",200,-10,10);

  h_FoM_smeared_avg[0] = new TH1F("h_FoM_smeared_avg[0]","h_FoM_smeared_avg[0]",500,0,0.5); 
  h_FoM_smeared_avg[1] = new TH1F("h_FoM_smeared_avg[1]","h_FoM_smeared_avg[1]",500,0,0.5); 
  h_FoM_smeared_avg[2] = new TH1F("h_FoM_smeared_avg[2]","h_FoM_smeared_avg[2]",500,0,0.5); 
  h_FoM_smeared_avg[3] = new TH1F("h_FoM_smeared_avg[3]","h_FoM_smeared_avg[3]",500,0,0.5); 
  h_FoM_smeared_avg[4] = new TH1F("h_FoM_smeared_avg[4]","h_FoM_smeared_avg[4]",500,0,0.5); 
  h_FoM_smeared_avg[5] = new TH1F("h_FoM_smeared_avg[5]","h_FoM_smeared_avg[5]",500,0,0.5); 
  h_FoM_smeared_avg[6] = new TH1F("h_FoM_smeared_avg[6]","h_FoM_smeared_avg[6]",500,0,0.5); 
  h_FoM_smeared_avg[7] = new TH1F("h_FoM_smeared_avg[7]","h_FoM_smeared_avg[7]",500,0,0.5); 

  h_FoM_smeared_MC = new TH1F("h_FoM_smeared_MC","h_FoM_smeared_MC",500,0,0.5); 

  h_Schmidt[0] = new TH1F("h_Schmidt[0]","h_Schmidt[0]",3000,0,3); 
  h_Schmidt[1] = new TH1F("h_Schmidt[1]","h_Schmidt[1]",3000,0,3); 
  h_Schmidt[2] = new TH1F("h_Schmidt[2]","h_Schmidt[2]",3000,0,3); 
  h_Schmidt[3] = new TH1F("h_Schmidt[3]","h_Schmidt[3]",3000,0,3); 
  h_Schmidt[4] = new TH1F("h_Schmidt[4]","h_Schmidt[4]",3000,0,3); 
  h_Schmidt[5] = new TH1F("h_Schmidt[5]","h_Schmidt[5]",3000,0,3); 
  h_Schmidt[6] = new TH1F("h_Schmidt[6]","h_Schmidt[6]",3000,0,3); 
  h_Schmidt[7] = new TH1F("h_Schmidt[7]","h_Schmidt[7]",3000,0,3); 
  h_Schmidt_gen = new TH1F("h_Schmidt_gen","h_Schmidt_gen",3000,0,3); 



