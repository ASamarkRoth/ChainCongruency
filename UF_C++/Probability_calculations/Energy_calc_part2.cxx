
    /////////////////////////////////////////////////////////////////////////////////////////////////
    // START ENERGY PART
    /////////////////////////////////////////////////////////////////////////////////////////////////

    /*    

  MyCanvas->cd(1);  

    f_name_first_Dubna.pop_back(); //Take away last "+"   
    f_name_first_Lund.pop_back(); //Take away last "+"
    f_name_first_BGS.pop_back(); //Take away last "+"
    TF1* total_first_Dubna = new TF1("hh",f_name_first_Dubna.c_str(),0,20);
    total_first_Dubna->SetNpx(100000); 
    TF1* total_first_Lund = new TF1("hh",f_name_first_Lund.c_str(),0,20);
    total_first_Lund->SetNpx(100000); 
    TF1* total_first_BGS = new TF1("hh",f_name_first_BGS.c_str(),0,20);
    total_first_BGS->SetNpx(100000);
    
    total_first_Dubna->GetXaxis()->SetRangeUser(9,11);
    total_first_Dubna->GetYaxis()->SetRangeUser(0,380);
        
    total_first_Dubna->SetLineColor(28); //marroon
    total_first_Dubna->Draw();
        
    total_first_Lund->SetLineColor(4);
    total_first_Lund->Draw("same");

    total_first_BGS->SetLineColor(7);
    total_first_BGS->Draw("same");




   //All this to calculate overlap energy integral for the first energy
 

    f_name_first_total.pop_back(); //Take away last "+"

 


  
    //Find normalisation constant
    TF1* total_first_energy_smeared = new TF1("hh",f_name_first_total.c_str(),0,20);
    total_first_energy_smeared->SetNpx(100000);

    //TEMPORARY SOLUTION
    total_first_energy_smeared->Draw("same");
    total_first_energy_smeared->SetLineColor(1);    
    //MyCanvas->cd(2);
    

    double integral_first = total_first_energy_smeared->Integral(alpha_lowlim,alpha_hilim);   //Make sure this integral is normalised
    if(print_E) {cout << "name is " <<  f_name_first_total << endl;}
    if(print_E) {cout << "integral is " << total_first_energy_smeared->Integral(alpha_lowlim,alpha_hilim)  << endl;} 
    
    if((int)(total_first_energy_smeared->Integral(alpha_lowlim,alpha_hilim)*10)%10 != 0) cout << "WARNING! Integration area too small!!!" << endl;   


    //Make a new function with the correct scaling factor, that can be plotted! 
    string f_name_first_total_norm = "(" + f_name_first_total + ")*[0]";                                    
    TF1* total_first_energy_smeared_normalised = new TF1("first_smeared_noralised",f_name_first_total_norm.c_str(),alpha_lowlim,alpha_hilim); //!!!
    total_first_energy_smeared_normalised->SetParameter(0,1.0/integral_first); 
    if(total_first_energy_smeared_normalised->Integral(alpha_lowlim,alpha_hilim) > 1.0001 || total_first_energy_smeared_normalised->Integral(alpha_lowlim,alpha_hilim) < 0.9999){cout << "AAAAAAAAARGH!!!!!" << total_first_energy_smeared_normalised->Integral(alpha_lowlim,alpha_hilim)  << endl;}

    //Construct the overlap integral
    string f_name_first_overlap = "pow(first";
    f_name_first_overlap += to_string(chain_to_evaluate);
    f_name_first_overlap += "*((";
    f_name_first_overlap += f_name_first_total;
    f_name_first_overlap += ")*1.0/";
    f_name_first_overlap += to_string(integral_first);
    f_name_first_overlap += "),1.0/2.0)";
    TF1 *energy_first_overlap = new TF1("energy",f_name_first_overlap.c_str(),alpha_lowlim,alpha_hilim); //!!!!!!!!    
    
    if(print_E) {cout << "the overlap string is now after adding the pow    " << f_name_first_overlap << endl;}

    cout << "The overlap between alpha 1 in chain " << chain_to_evaluate << " and the other short chains is " << energy_first_overlap->Integral(alpha_lowlim,alpha_hilim) << endl;
    
    //Now, PLOT!

    //Reference distribution    
    total_first_energy_smeared_normalised->SetNpx(100000);
    total_first_energy_smeared_normalised->SetLineColor(6);
    total_first_energy_smeared_normalised->GetXaxis()->SetRangeUser(alpha_lowlim,alpha_hilim); //!!!!!!!
    total_first_energy_smeared_normalised->GetYaxis()->SetRangeUser(0,50);
    total_first_energy_smeared_normalised->Draw();

    //Energy to test
    string f_to_evaluate;
    f_to_evaluate = "first";
    f_to_evaluate += to_string(chain_to_evaluate);
    TF1 *energy_first_to_evaluate = new TF1("energy",f_to_evaluate.c_str(),alpha_lowlim,alpha_hilim);  
    energy_first_to_evaluate->SetLineColor(7); 
    energy_first_to_evaluate->SetNpx(100000); 
    energy_first_to_evaluate->Draw("same"); 

    //Energy overlap function
    energy_first_overlap->SetNpx(100000);
    energy_first_overlap->SetLineColor(4);
    energy_first_overlap->Draw("same");

    //Legend
    TLegend *leg = new TLegend(0.50,0.50,0.85,0.85);
    leg->SetTextSize(0.05);  
    leg->SetFillStyle(0);  
    leg->AddEntry(total_first_energy_smeared_normalised,"reference","l");
    leg->AddEntry(energy_first_to_evaluate,"to evaluate","l");
    leg->AddEntry(energy_first_overlap,"overlap","l");
    leg->Draw("same");
    




   

    ////////////////////////////////////////////////////////////////////////////////////////

    //MyCanvas->cd(3);

    f_name_second_total.pop_back(); //Take away last "+"
  
    //Find normalisation constant
    TF1* total_second_energy_smeared = new TF1("hh",f_name_second_total.c_str(),0,20);
    total_second_energy_smeared->SetNpx(100000);
    double integral_second = total_second_energy_smeared->Integral(alpha_lowlim,alpha_hilim);   //Make sure this integral is normalised
    if(print_E) cout << "name is " <<  f_name_second_total << endl;
    if(print_E)cout << "integral is " << total_second_energy_smeared->Integral(alpha_lowlim,alpha_hilim)  << endl; 
    if((int)(total_second_energy_smeared->Integral(alpha_lowlim,alpha_hilim)*10)%10 != 0) cout << "WARNING! Integration area too small!!!" << endl;       

    //Make a new function with the correct scaling factor, that can be plotted! 
    string f_name_second_total_norm = "(" + f_name_second_total + ")*[0]";                                    
    TF1* total_second_energy_smeared_normalised = new TF1("second_smeared_noralised",f_name_second_total_norm.c_str(),alpha_lowlim,alpha_hilim); //!!!
    total_second_energy_smeared_normalised->SetParameter(0,1.0/integral_second); 
    if(total_second_energy_smeared_normalised->Integral(alpha_lowlim,alpha_hilim) > 1.0001 || total_second_energy_smeared_normalised->Integral(alpha_lowlim,alpha_hilim) < 0.9999){cout << "AAAAAAAAARGH!!!!!" << total_second_energy_smeared_normalised->Integral(alpha_lowlim,alpha_hilim)  << endl;}



    //Construct the overlap integral
    string f_name_second_overlap = "pow(second";
    f_name_second_overlap += to_string(chain_to_evaluate);
    f_name_second_overlap += "*((";
    f_name_second_overlap += f_name_second_total;
    f_name_second_overlap += ")*1.0/";
    f_name_second_overlap += to_string(integral_second);
    f_name_second_overlap += "),1.0/2.0)";
    TF1 *energy_second_overlap = new TF1("energy",f_name_second_overlap.c_str(),alpha_lowlim,alpha_hilim); //!!!!!!!!    
    
    if(print_E) cout << "the overlap string is now after adding the pow    " << f_name_second_overlap << endl;

    cout << "The overlap between alpha 2 in chain " << chain_to_evaluate << " and the other short chains is " << energy_second_overlap->Integral(alpha_lowlim,alpha_hilim) << endl;
    
    //Now, PLOT!

    //Reference distribution    
    total_second_energy_smeared_normalised->SetNpx(100000);
    total_second_energy_smeared_normalised->SetLineColor(6);
    total_second_energy_smeared_normalised->GetXaxis()->SetRangeUser(alpha_lowlim,alpha_hilim); //!!!!!!!
    total_second_energy_smeared_normalised->GetYaxis()->SetRangeUser(0,50);
    total_second_energy_smeared_normalised->Draw();

    //Energy to test
    
    f_to_evaluate = "second";
    f_to_evaluate += to_string(chain_to_evaluate);
    TF1 *energy_second_to_evaluate = new TF1("energy",f_to_evaluate.c_str(),alpha_lowlim,alpha_hilim);  
    energy_second_to_evaluate->SetLineColor(7); 
    energy_second_to_evaluate->SetNpx(100000); 
    energy_second_to_evaluate->Draw("same"); 

    //Energy overlap function
    energy_second_overlap->SetNpx(100000);
    energy_second_overlap->SetLineColor(4);
    energy_second_overlap->Draw("same");

    //Legend
    TLegend *leg2 = new TLegend(0.50,0.50,0.85,0.85);
    leg2->SetTextSize(0.05);  
    leg2->SetFillStyle(0);  
    leg2->AddEntry(total_second_energy_smeared_normalised,"reference","l");
    leg2->AddEntry(energy_second_to_evaluate,"to evaluate","l");
    leg2->AddEntry(energy_second_overlap,"overlap","l");
    leg2->Draw("same");


    //PLot separate smeared distributions
    //MyCanvas->cd(4);

    f_name_second_Dubna.pop_back(); //Take away last "+"   
    f_name_second_Lund.pop_back(); //Take away last "+"
    f_name_second_BGS.pop_back(); //Take away last "+"
    TF1* total_second_Dubna = new TF1("hh",f_name_second_Dubna.c_str(),0,20);
    total_second_Dubna->SetNpx(100000); 
    TF1* total_second_Lund = new TF1("hh",f_name_second_Lund.c_str(),0,20);
    total_second_Lund->SetNpx(100000); 
    TF1* total_second_BGS = new TF1("hh",f_name_second_BGS.c_str(),0,20);
    total_second_BGS->SetNpx(100000);
    
    total_second_Dubna->GetXaxis()->SetRangeUser(9,11);
    total_second_Dubna->GetYaxis()->SetRangeUser(0,480);
        
    total_second_Dubna->SetLineColor(28); //marroon
    total_second_Dubna->Draw();
        
    total_second_Lund->SetLineColor(4);
    total_second_Lund->Draw("same");

    total_second_BGS->SetLineColor(7);
    total_second_BGS->Draw("same");

    total_second_energy_smeared->SetNpx(100000);
    total_second_energy_smeared->SetLineColor(1);
    total_second_energy_smeared->Draw("same");
    
    */

    //////////////////////////////////////////////////////////////////////////////////////////////
    // ENDS THE ENERGY PART
    //////////////////////////////////////////////////////////////////////////////////////////////    
