void find_conf_limits(TH1F* h_sim_dist){

  int number_in_histo = h_sim_dist->Integral();  
  int nr_of_bins = h_sim_dist->GetSize()-2;
  double nr_of_bins_per_unit = nr_of_bins/(h_sim_dist->GetXaxis()->GetXmax()-h_sim_dist->GetXaxis()->GetXmin());

  //Upper 3-sigma limit 
  int q = 0;
  while (h_sim_dist->Integral(q,nr_of_bins)/number_in_histo > 0.0015){
    q++;
  }
  double qd = q;
  qd /= nr_of_bins_per_unit;
  cout << "Upper 3-sigma limit is " << qd << endl;


  //Upper 1% limit 
  int v = 0;
  while (h_sim_dist->Integral(v,nr_of_bins)/number_in_histo > 0.01){
    v++;
  }
  double vd = v;
  vd /= nr_of_bins_per_unit;
  cout << "Upper 1% limit is " << vd << endl;



  //Upper 2-sigma limit 
  int w = 0;
  while (h_sim_dist->Integral(w,nr_of_bins)/number_in_histo > 0.023){
    w++;
  }
  double wd = w;
  wd /= nr_of_bins_per_unit;
  cout << "Upper 2-sigma limit is " << wd << endl;
  


  
  //Find upper 5% limit
  int u = 0;
  while (h_sim_dist->Integral(u,nr_of_bins)/number_in_histo > 0.05){ //0.05
    u++;
  }
  double ud = u;
  ud /= nr_of_bins_per_unit;
  cout << " Upper 5% limit is " << ud << endl;


  //Find upper 1-sigma limit
  int r = 0;
  while (h_sim_dist->Integral(r,nr_of_bins)/number_in_histo > 0.1585){ //0.05
    r++;
  }
  double rd = r;
  rd /= nr_of_bins_per_unit;
  cout << " Upper 1-sigma limit is " << rd << endl;




  cout << "Average value is " << h_sim_dist->GetMean()  << endl;
  


  //Find lower 1-sigma limit
  int z = nr_of_bins;
  while (h_sim_dist->Integral(0,z)/number_in_histo > 0.1585){  //0.05
    z--;
  }
  double zd = z;
  zd /= nr_of_bins_per_unit;
  cout << "Lower 1-sigma limit is " << zd << endl;
  


  
  //Find lower 5% limit
  int s = nr_of_bins;
  while (h_sim_dist->Integral(0,s)/number_in_histo > 0.05){  //0.05
    s--;
  }
  double sd = s;
  sd /= nr_of_bins_per_unit;
  cout << "Lower 5% limit is " << sd << endl;
  
  
  //Find lower 2-sigma limit
  int c = nr_of_bins;
  while (h_sim_dist->Integral(0,c)/number_in_histo > 0.023){  //0.05
    c--;
  }
  double cd = c;
  cd /= nr_of_bins_per_unit;
  cout << "Lower 2-sigma limit is " << cd << endl;


  //Find lower 1% limit
  int t = nr_of_bins;
  while (h_sim_dist->Integral(0,t)/number_in_histo > 0.01){
    t--;
  }
  double td = t;
  td /= nr_of_bins_per_unit;
  cout << "Lower 1% limit is " << td << endl;


  //Find lower 3-sigma limit
  int b = nr_of_bins;
  while (h_sim_dist->Integral(0,b)/number_in_histo > 0.0015){
    b--;
  }
  double bd = b;
  bd /= nr_of_bins_per_unit;
  cout << "Lower 3-sigma limit is " << bd << endl;


  //To construct strength function

  //cout<< "The prob to be within the 90% interval is " << h_sim_dist->Integral(0.193*nr_of_bins_per_unit,0.264*nr_of_bins_per_unit)/number_in_histo << endl;

  //  cout<< "The prob to be within the 90% interval is " << h_sim_dist->Integral(0.181*nr_of_bins_per_unit,0.255*nr_of_bins_per_unit)/number_in_histo << endl;
 //for fixed and not SimAvgTimes

 
}




int max_in_array(int *array, int array_length ){
	int temp = 0;
	for (int i = 0; i< array_length; i++){
		temp = max(temp,array[i]);
	}
	return temp;
}

int max_in_array(vector<int> array, int array_length ){
	int temp = 0;
	for (int i = 0; i< array_length; i++){
		temp = max(temp,array[i]);
	}
	return temp;
}

//Test if the time from a certain event should be used
bool use_event(int iStep, int f){
  bool use_exp_time = false;	    

  if (iStep == 0){  
    if(all_chains[f][9] > 0){
      if(!random_chains){
	if(f != 1318 && f != 2015){  //if(f != 1318)
	  use_exp_time = true;
	}
      }
      else{
	if(  (scenario != 477 || f%96!=49) &&  (scenario != 482 || f%30!=29)   ){ //if(scenario != 477 || f%96!=49 ){
	  use_exp_time = true;
	}
      } 
    }
  }
  


    else if (iStep == 1){  //Two special chains
      if(all_chains[f][9+iStep*3] > 0){
	if(!random_chains){
	  if(all_chains[f][6+iStep*3] > 0 || f == 1614 || f == 1629){
	    use_exp_time = true;
	  }
	}
	else{
	  if(all_chains[f][6+iStep*3] > 0 || ( (f%96==67 || f%96==82) && scenario==477 ) ){
	    use_exp_time = true;
	  }
	}   
      } //if temp > 0
    }   




  else if (iStep == 4){ //One special chain
    if(all_chains[f][9+iStep*3] > 0){
      if(!random_chains){
	if(all_chains[f][6+iStep*3] > 0 || f == 1302){
	  use_exp_time = true;
	}
      }
      else{ 
	if(all_chains[f][6+iStep*3] > 0 || (f%96==33 && scenario == 477 )){
	  use_exp_time = true;
	}
      }
    } //if temp > 0
  }
  

  ///////////////////////
  // Un-comment this for E115, long
  ///////////////////////
  
  //Do not require the previous to exist (such long times anyway for E115). 
  else if (iStep == 5){  
    if (all_chains[f][24] > 0){
      use_exp_time = true;
    }     
  }
  

  else{   
    if(all_chains[f][6+iStep*3] > 0 && all_chains[f][9+iStep*3] > 0){
      use_exp_time = true;
    }
  }

  return use_exp_time;

}








//Print FoM to screen 
void print_FoM_smeared(double FoM){

  cout << fixed << setprecision(0);

  if(FoM < 10 && FoM > 0){cout << fixed << setprecision(3);}
  //if(FoM < 1 && FoM  > 0){cout << fixed << setprecision(3);}

  if(FoM > 0){cout << "& \t " << FoM << " \t ";}
  else if (FoM == 0) cout << "& \t " << "n/a " << " \t ";
  else cout << "Problem! FoM is " << FoM << endl;

  cout << fixed << setprecision(6);

}



//Calculate FoM
double calc_FoM_smeared(int nr_in_set, double average_time, double t){

  /*
  //This is the Jackie-version of normalisation
  TF1 *norm_gf_ref_pdf_logbins = new TF1("norm_gf_ref_pdf_logbins","[2]*x*pow([1],[0]-1)/(pow([0]*[1]+x,[0])*exp([0]))",log_lowlim,log_hilim); //[0] = n, [1] = t-bar, [2] = gamma_norm_factor
  double gamma_norm_factor = 1.0/(gsl_sf_gamma_inc(2.0-nr_in_set,nr_in_set) - nr_in_set*gsl_sf_gamma_inc(1.0-nr_in_set,nr_in_set));
  norm_gf_ref_pdf_logbins->SetParameter(0,nr_in_set);  //nr_in_set
  norm_gf_ref_pdf_logbins->SetParameter(1,average_time); //!!!!!!!!!!!!!!!!!!!!!!! NOT CORRECT FOR RANDOM CHAINS ?????
  norm_gf_ref_pdf_logbins->SetParameter(2,gamma_norm_factor); 
  */

  /*
  //This is the non-Jackie version of normalisation
  TF1 *norm_ref_pdf_logbins = new TF1("norm_ref_pdf_logbins","x*pow([0]*[1],[0]-1)*2.0*(2*[0]-1)/(pow([0]*[1]+x,[0]))",log_lowlim,log_hilim); //[0] = n (nr_in_set), [1] = t-bar
  norm_ref_pdf_logbins->SetParameter(0,nr_in_set);  //nr_in_set
  norm_ref_pdf_logbins->SetParameter(1,average_time);  //n
  */

  //This is the non-normalised-to-one. (So integral is normalised)


  
  TF1 *ref_pdf_logbins = new TF1("ref_pdf_logbins","x*([0]-1)*pow([0]*[1],[0]-1)/(pow([0]*[1]+x,[0]))",log_lowlim,log_hilim); //[0] = n (nr_in_set), [1] = time. This is the proper routine
  ref_pdf_logbins->SetParameter(0,nr_in_set);  //nr_in_set
  ref_pdf_logbins->SetParameter(1,average_time);  //Either t-bar-exp OR average time of all simulated chains. Have to pick...
 

  /*  
  TF1 *ref_pdf_logbins = new TF1("ref_pdf_logbins","x/[0]*exp(-x/[0])",log_lowlim,log_hilim); //[0] = n (nr_in_set), [1] = time. This is the non-smeared routine
  ref_pdf_logbins->SetParameter(0,average_time);  //Either t-bar-exp OR average time of all simulated chains. Have to pick...  
  //cout << endl << endl << "watcH OUT! modified routine to non-smeared!" << endl << endl;
  */


  /*
  TF1 *ref_pdf_logbins = new TF1("ref_pdf_logbins","x*([0]-1)*pow([0]*[1],[0]-1)/(pow([0]*[1]+x,[0]))",log_lowlim,log_hilim); //[0] = n (nr_in_set), [1] = time. This is the proper routine
  ref_pdf_logbins->SetParameter(0,4);  //nr_in_set
  ref_pdf_logbins->SetParameter(1,average_time);  //Either t-bar-exp OR average time of all simulated chains. Have to pick...
 
  cout << endl << endl << "watcH OUT! modified routineto N=4!" << endl << endl;
  */



  /*
  cout << "Test!"<< endl;
  cout << "nr_in_set is "<< nr_in_set << endl;
  cout << "average_time is "<< average_time << endl;
  cout << "t is " << t << endl;
  cout << norm_ref_pdf_logbins->Eval(t) << endl;
  */

  double temp = ref_pdf_logbins->Eval(t);
  delete ref_pdf_logbins;
  return temp;
 
}



//Routine to read in chains
void readin(string chainX){
  int m = 0;
  int chain_number = 0;
  double temp = 0;
  ifstream chain(chainX.c_str(),ios::in);
  while (chain>>temp){
    if (m==0) {
      chain_number = temp;
      all_chains[chain_number][m] = chain_number;
      m++;
    } 
    //OBS; some custimization inside routine, which makes it non-general
    else if (m==1) {all_chains[chain_number][m] = temp; m++;} //Beam energy

    else if (m==2) {all_chains[chain_number][m] = temp; m++;} //Strip-x number

    else if (m==3) {all_chains[chain_number][m] = temp; m++;} //Strip-y number

    else if (m==4) {all_chains[chain_number][m] = temp; m++;} //Pixel number

    else if (m==5) {h_implant_energy->Fill(temp);  all_chains[chain_number][m] = temp; m++;} 

    else if (m==6) {all_chains[chain_number][m] = temp; m++;}  // Imp. time == 0 

    else if (m==7) {h_decay_energy[0]->Fill(temp);  all_chains[chain_number][m] = temp; m++;}

    else if (m==8) {all_chains[chain_number][m] = temp; m++;}//Energy uncertainty, sigma

    //else if (m==9) {if(temp > 0 && ( chain_number != 1318 || random_chains) ){h_decay_time[0]->Fill(temp); h_decay_time_logbins[0]->Fill(temp); h_decay_time_ln[0]->Fill(log(temp));}  all_chains[chain_number][m] = temp; m++;} //Time one

    else if (m==9) {
      all_chains[chain_number][m] = temp; 
      m++;
      if(temp > 0){
	if(!random_chains){
	  if(chain_number != 1318 && chain_number != 2015 ){  // if(chain_number != 1318 ){
	    h_decay_time[0]->Fill(temp);
	    h_decay_time_logbins[0]->Fill(temp);
	    h_decay_time_ln[0]->Fill(log(temp));
	  }
	}
	else{
	  if( (scenario != 477 || chain_number%96!=49) && (scenario != 482 || chain_number%30!=29)  ){
	    h_decay_time[0]->Fill(temp);
	    h_decay_time_logbins[0]->Fill(temp);
	    h_decay_time_ln[0]->Fill(log(temp));
	  }
	} 
    }//if temp>0
} //Time one

    else if (m==10) {h_decay_energy[1]->Fill(temp);  all_chains[chain_number][m] = temp; m++;}

    else if (m==11) {all_chains[chain_number][m] = temp; m++;} //Uncertainty
    


    else if (m==12){
      all_chains[chain_number][m] = temp; 
      if(temp > 0){
	if(!random_chains){
	  if(all_chains[chain_number][m-3] > 0 || chain_number == 1614 || chain_number == 1629){
	    h_decay_time[1]->Fill(temp); 
	    h_decay_time_logbins[1]->Fill(temp);  
	    h_decay_time_ln[1]->Fill(log(temp));
	  }
	}
	else{
	  if(all_chains[chain_number][m-3] > 0 || ( (chain_number%96==67 || chain_number%96==82) && scenario==477 ) ){
	    h_decay_time[1]->Fill(temp); 
	    h_decay_time_logbins[1]->Fill(temp);  
	    h_decay_time_ln[1]->Fill(log(temp));
	  }
	}   
      } //if temp > 0
      m++;
    }      




    else if (m==13) {h_decay_energy[2]->Fill(temp);  all_chains[chain_number][m] = temp; m++;}

    else if (m==14) {all_chains[chain_number][m] = temp; m++;} //Uncert

    else if (m==15) {if(temp > 0 && all_chains[chain_number][m-3] > 0){h_decay_time[2]->Fill(temp); h_decay_time_logbins[2]->Fill(temp); h_decay_time_ln[2]->Fill(log(temp));}  all_chains[chain_number][m] = temp; m++;}
 
   else if (m==16) {h_decay_energy[3]->Fill(temp);  all_chains[chain_number][m] = temp; m++;}

    else if (m==17) {all_chains[chain_number][m] = temp; m++;} //Uncert

    else if (m==18) {if(temp > 0 && all_chains[chain_number][m-3] > 0){h_decay_time[3]->Fill(temp); h_decay_time_logbins[3]->Fill(temp);  h_decay_time_ln[3]->Fill(log(temp));} all_chains[chain_number][m] = temp; m++;}

    else if (m==19) {h_decay_energy[4]->Fill(temp);  all_chains[chain_number][m] = temp; m++;}

    else if (m==20) {all_chains[chain_number][m] = temp; m++;} //Uncert



    else if (m==21){ 
      all_chains[chain_number][m] = temp; 
      if(temp > 0){
	if(!random_chains){
	  if(all_chains[chain_number][m-3] > 0 || chain_number == 1302){
	    h_decay_time[4]->Fill(temp); 
	    h_decay_time_logbins[4]->Fill(temp);   
	    h_decay_time_ln[4]->Fill(log(temp));
	  }
	}
	else{ 
	  if(all_chains[chain_number][m-3] > 0 || (chain_number%96==33 && scenario == 477) ){
	    h_decay_time[4]->Fill(temp); 
	    h_decay_time_logbins[4]->Fill(temp);   
	    h_decay_time_ln[4]->Fill(log(temp)); 
	  }
	}
      } //if temp > 0
      m++;
    }


    else if (m==22) {h_decay_energy[5]->Fill(temp);  all_chains[chain_number][m] = temp; m++;}

    else if (m==23) {all_chains[chain_number][m] = temp; m++;} //Uncert


    ////////////
    //Choose this for E115, long
    ////////////

    else if (m==24) {if(temp > 0 ) {h_decay_time[5]->Fill(temp); h_decay_time_logbins[5]->Fill(temp);  h_decay_time_ln[5]->Fill(log(temp));} all_chains[chain_number][m] = temp; m++;} //OBS!!! Here, a previous time should not be required; so long times anyway! 

    ////////////
    //Choose this for normal cases, where we always require a previous time!
    ////////////

    //else if (m==24) {if(temp > 0 && all_chains[chain_number][m-3] > 0) {h_decay_time[5]->Fill(temp); h_decay_time_logbins[5]->Fill(temp);  h_decay_time_ln[5]->Fill(log(temp));} all_chains[chain_number][m] = temp; m++;} //OBS!!! Here, a previous time should not be required; so long times anyway! But for E117, the requirement should be there!




     else if (m==25) {h_decay_energy[6]->Fill(temp);  all_chains[chain_number][m] = temp; m++;}

     else if (m==26) {all_chains[chain_number][m] = temp; m++;} //Uncert

    else if (m==27) {if(temp > 0 && all_chains[chain_number][m-3] > 0) {h_decay_time[6]->Fill(temp); h_decay_time_logbins[6]->Fill(temp);  h_decay_time_ln[6]->Fill(log(temp));} all_chains[chain_number][m] = temp; m++;}

    else if (m==28) {h_decay_energy[7]->Fill(temp);  all_chains[chain_number][m] = temp; m++;}

    else if (m==29) {all_chains[chain_number][m] = temp; m++;}

    else if (m==30) {if(temp > 0 && all_chains[chain_number][m-3] > 0) {h_decay_time[7]->Fill(temp); h_decay_time_logbins[7]->Fill(temp);  h_decay_time_ln[7]->Fill(log(temp));} all_chains[chain_number][m] = temp; m++;}
  }
  chain.close();
  //cout << "Times are " << all_chains[chain_number][8] <<" "<< all_chains[chain_number][10]<< " and " <<  all_chains[chain_number][12] <<endl;
}




//Calculates overlap of two functions
double overlap(double halflife_ref, double avg_time){

  //Create a function!
  TF1 *ftotest = new TF1("ftotest","[0]*exp(x+log([1]))*exp(-exp(x+log([1])))",-100,100);  //n-noll = [0], lambda = [1]
  ftotest->SetParameter(0,1);
  ftotest->SetParameter(1,(1/(avg_time)));
  ftotest->SetNpx(1000);

  //Create another function
  TF1 *fref = new TF1("fref","[0]*exp(x+log([1]))*exp(-exp(x+log([1])))",-100,100);  //n-noll = [0], lambda = [1]
  fref->SetParameter(0,1);
  fref->SetParameter(1,(log(2)/halflife_ref));  //ref is given in half-life!!!
  fref->SetNpx(1000);

  //Create a new function from the previous ones
  TF1 *foverlap = new TF1("foverlap", "sqrt(fref*ftotest)",-100,100);
  foverlap->SetNpx(1000);

  //Now, lets calculate integrals
  double integral_to_test = 0;
  double integral_ref = 0;
  double integral_overlap = 0; 
  integral_to_test = ftotest->Integral(-100,100);
  integral_ref = fref->Integral(-100,100);
  integral_overlap = foverlap->Integral(-100,100);

  bool print_method1 = 0;
  //Print and draw
  if(print_method1){ 
    cout << "Integral of ftotest is " << integral_to_test << endl;
    cout << "Integral of fref is " << integral_ref << endl; 
    cout << "Integral of foverlap is " << integral_overlap << endl; 
    ftotest->SetLineColor(90);
    ftotest->Draw();
    fref->Draw("same");
    foverlap->SetLineColor(80);
    foverlap->Draw("same"); }

  return integral_overlap;
  
}
