  //     //////////////////////////////////////////////////////////////
  //     //Fill smeared energy histos
  //     //////////////////////////////////////////////////////////////
 
      

  // //FIRST
    

  //     first_energy_smeared->SetParameter(1,all_chains[f][7]);
  //     first_energy_smeared->SetParameter(2,all_chains[f][8]/1000.0); 
      
      
  //     if(all_chains[f][8] > 0 && all_chains[f][7] > 0){
  // 	first_energy_smeared->SetParameter(0,1.0/(all_chains[f][8]/1000.0 * sqrt(2.0*TMath::Pi())));
  //     }//ends if(all_chains[f][8] > 0 && all_chains[f][7] > 0)
      
  //     else {
  // 	cout << "Chain " << f << " does not have a proper first alpha energy, put the height of the Gaussian to zero." << endl;
  // 	first_energy_smeared->SetParameter(0,0.0);
  //     }

	
  // 	/*	
  // 		TCanvas *MyCanvas = new TCanvas("MyCanvas");
  // 		MyCanvas->Divide(1,1);
  // 		MyCanvas->cd(1);
  // 		first_energy_smeared->Draw();
  // 		MyCanvas->Print("output.pdf");
  // 		cout << "f is now " << f << endl;	
  // 	*/
	
  // 	/*
  // 	  double first_norm_integral = first_energy_smeared->Integral(9,12); 
  // 	  first_energy_smeared->SetParameter(0,1.0/first_norm_integral);
  // 	  cout << "LOOK HERE!!! First_norm_integral is " << first_norm_integral << endl; 
  // 	  cout << all_chains[f][7] << endl;
  // 	  cout << all_chains[f][8]/1000.0 << endl;
  // 	  return 0;
  // 	*/
	
  // 	//Make a string with the name (e.g.) "first1401"
  // 	string f_name_first;
  // 	f_name_first = "first";
  // 	f_name_first += to_string(f);
	
  // 	//Store the normalised Gaussian belonging to (e.g.) chain 1401 under the name "first1401" in an array
  // 	first[f] = (TF1*)first_energy_smeared->Clone(f_name_first.c_str());
	
  // 	//Make a string with (e.g.) "first1401 + first1402 + ..."
  // 	f_name_first_total = f_name_first_total + f_name_first + "+";      

  // 	//Separate into different strings depending on Lund/Dubna/BGS
  // 	if(f > 1000 && f < 1300) f_name_first_Dubna += f_name_first + "+";
  // 	if(f > 1300 && f < 1600) f_name_first_Lund += f_name_first + "+";
  // 	if(f > 1600 && f < 1900) f_name_first_BGS += f_name_first + "+";


  // 	//Remove the one chain we want to evaluate agains the others 
  // 	if(energy_calc){
  // 	  if(f == chain_to_evaluate){
  // 	    for(int t = 0; t <10; t++){f_name_first_total.pop_back();}
  // 	  }
  // 	}
	
   
      
  //     ////////////////////////////////////////////////////////////////////


  //     //SECOND

  //   	second_energy_smeared->SetParameter(1,all_chains[f][10]);
  // 	second_energy_smeared->SetParameter(2,all_chains[f][11]/1000.0); 

  //     if(all_chains[f][10] > 0 && all_chains[f][11] > 0){
  // 	second_energy_smeared->SetParameter(0,1.0/(all_chains[f][11]/1000.0 * sqrt(2.0*TMath::Pi())));
  //     }
  //     else {
  // 	cout << "chain " << f << " does not have a proper second alpha energy, put the height of the Gaussian to zero." << endl;
  // 	second_energy_smeared->SetParameter(0,0.0);
  //     }
      
	
  // 	/*	
  // 		TCanvas *MyCanvas = new TCanvas("MyCanvas");
  // 		MyCanvas->Divide(1,1);
  // 		MyCanvas->cd(1);
  // 		second_energy_smeared->Draw();
  // 		MyCanvas->Print("output.pdf");
  // 		cout << "f is now " << f << endl;	
  // 	*/
	
  // 	/*
  // 	  double second_norm_integral = second_energy_smeared->Integral(9,12); 
  // 	  second_energy_smeared->SetParameter(0,1.0/second_norm_integral);
  // 	  cout << "LOOK HERE!!! Second_norm_integral is " << second_norm_integral << endl; 
  // 	  cout << all_chains[f][7] << endl;
  // 	  cout << all_chains[f][8]/1000.0 << endl;
  // 	  return 0;
  // 	*/
	
  // 	//Make a string with the name (e.g.) "second1401"
  // 	string f_name_second;
  // 	f_name_second = "second";
  // 	f_name_second += to_string(f);
	
  // 	//Store the normalised Gaussian belonging to (e.g.) chain 1401 under the name "second1401" in an array
  // 	second[f] = (TF1*)second_energy_smeared->Clone(f_name_second.c_str());
	
  // 	//Make a string with (e.g.) "second1401 + second1402 + ..."
  // 	f_name_second_total = f_name_second_total + f_name_second + "+";

  // 	//Separate into different strings depending on Lund/Dubna/BGS
  // 	if(f > 1000 && f < 1300) f_name_second_Dubna += f_name_second + "+";
  // 	if(f > 1300 && f < 1600) f_name_second_Lund += f_name_second + "+";
  // 	if(f > 1600 && f < 1900) f_name_second_BGS += f_name_second + "+";

      
  // 	//Remove the one chain we want to evaluate agains the others 
  // 	if(energy_calc){
  // 	  if(f == chain_to_evaluate){
  // 	    for(int t = 0; t <11; t++){f_name_second_total.pop_back();}
  // 	  }
  // 	}
	
 
      
  //     ////////////////////////////////////////////////////////////////////


	

      //////////////////////
      //COUNTER!
      //////////////////////
      counter++;
      //////////////////////

      ////////////////////////////////////////////////////
      //Smeared energy histos done!
      ///////////////////////////////////////////////////