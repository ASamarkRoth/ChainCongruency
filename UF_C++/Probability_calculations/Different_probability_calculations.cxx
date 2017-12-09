#include <iostream>
#include <ctime>
#include <random>
#include <iomanip>
#include <algorithm>
#include <iterator>
#include <string>
#include <sstream>
#include "TH1.h"
#include "TFile.h"
#include "TF1.h"
#include <fstream>
#include "TMath.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TGaxis.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TStyle.h"
#include <gsl/gsl_math.h>
#include <gsl/gsl_sf.h>
#include <vector>

using namespace std;

//Define how to use the code:
bool ask = 0;
bool type_in_values = 0;
bool read_values_from_file = 1;
bool plot_a_lot = 1;
bool short_chains = 0;
bool random_chains = 0;
bool print_E = 0;
bool FoM_up_and_low_lim = 0;    
bool print_FoM = 0;
bool print_smeared_FoM = 1;
bool print_smeared_FoM_to_screen = 0;
bool energy_calc = 0;
bool real_chains = 0;

bool ind_tbar_param = 1; //Takes a few more sec to have this

double alpha_lowlim = 9.0; 
double alpha_hilim = 12.0;                

const int max_chain_length = 3; //How many steps to consider


//Functions
double overlap(double halflife_ref, double avgtime);
void readin(string chainX);
double calc_FoM_smeared(int nr_in_set, double average_time, double t);
void print_FoM_smeared(double FoM);
bool use_event(int iStep, int f);
int max_in_array(int *array, int array_length );
int max_in_array(vector<int> array, int array_length );
void find_conf_limits(TH1F* h_sim_dist);

/*
void prep_first_histo_to_plot(TH1F* h_first_histo_to_plot, string xaxis, string yaxis, double lowx, double highx, double lowy, double highy);
{
 h_first_histo_to_plot->SetTitle("");
 h_first_histo_to_plot->SetStats(0);
 h_first_histo_to_plot->GetXaxis()->SetTitle("xaxis");
 h_first_histo_to_plot->GetYaxis()->SetTitle("yaxis");
 h_first_histo_to_plot->GetXaxis()->SetTitleOffset(1.2);
 h_first_histo_to_plot->GetYaxis()->SetTitleOffset(1.0);
 h_first_histo_to_plot->GetXaxis()->CenterTitle();
 h_first_histo_to_plot->GetYaxis()->CenterTitle();
 h_first_histo_to_plot->GetXaxis()->SetRangeUser(0.41,1.49);
 h_first_histo_to_plot->GetYaxis()->SetRangeUser(0.1,59999);
 h_first_histo_to_plot->GetYaxis()->SetDecimals(2);
}
*/



#include "global_variables.cxx" 



//Main function
int main(){

  ofstream to_file_2("single_tvasteg.txt",ios::out);


#include "main_variables.cxx"

	int index = 0;

	int maximum_nr_of_chains = 0;  

	//Make nice-looking histograms
#include "make_histos_look_nice.cxx"


	//Select reference half-lives ("scenario")
	if(!short_chains){
		cout << "Scenario? (to choose later, take scenario 0) ";
		cin >> scenario;
	}

	if(energy_calc){
		cout << "chain to evaluate for energy calculation ";
		cin >> chain_to_evaluate;
	}


	//cout << "WARNING!!!!!!!!! Now, the average time for each set is used!" << endl;


	//This is the list with all scenarios - halflives, numbers, and (for random chains) the number of sets. Also calculates maximum number of steps
#include "scenario_time_and_number.cxx"

	//Print seleted reference half-lives
	cout << fixed << setprecision(5);
	cout << "Selected values: " << endl;
	cout << "Half-lives       nr_in_step" << endl;
	for (int iStep = 0; iStep < max_chain_length; iStep++){ 
		cout <<  halflife_ref[iStep]  <<  "         "   << nr_in_step[iStep]  << endl;
	}

	maximum_nr_of_chains = max_in_array(chains_to_consider, allowed_nr_of_chains);

//	if (!random_chains){
//		maximum_nr_of_chains = max_in_array(chains_to_consider, allowed_nr_of_chains);
//	}
	
	if(random_chains){
	//	maximum_nr_of_chains = allowed_nr_of_chains/1;  //!!!!!!!!!!!! full glory
		maximum_nr_of_chains = maximum_nr_of_chains / 1;
	} 
//	else{maximum_nr_of_chains = max_in_array(chains_to_consider, allowed_nr_of_chains);
//	} //Unnnessasary to loop over more than this

	cout << "Maximum_nr_of_chains: " << maximum_nr_of_chains << endl;
	all_chains.resize(maximum_nr_of_chains+1,vector<double>(25,0.0));    //MAY NEED TO INCREASE THIS!
	chains_to_consider.resize(maximum_nr_of_chains+1);

	vector<vector<vector<double>>> FoMSmearedSim(nr_of_sets_of_random_chains,vector<vector<double>>(nr_of_chains_in_set,vector<double>(max_chain_length,0.0)));


	vector<double>  FoM_smeared_sim_geom_avg;
	FoM_smeared_sim_geom_avg.resize(nr_of_sets_of_random_chains,0.0);
	
	vector< vector< double> > FoM_smeared_sim_geom;
	FoM_smeared_sim_geom.resize(nr_of_sets_of_random_chains,vector<double>(nr_of_chains_in_set,0.0));
	
	vector< vector< double> > SimAvgTimes;
	SimAvgTimes.resize(nr_of_sets_of_random_chains,vector<double>(allowed_max_chain_length,0.0));

	vector< vector< double> > SimAvgThetas;
	SimAvgThetas.resize(nr_of_sets_of_random_chains,vector<double>(allowed_max_chain_length,0.0));

	vector< vector< double> > FoM_sim_smeared_avg;
	FoM_sim_smeared_avg.resize(nr_of_sets_of_random_chains, vector<double>(allowed_max_chain_length,0.0));
	
	vector< vector< double> > theta_sigma_sim;
	theta_sigma_sim.resize(nr_of_sets_of_random_chains,vector<double>(allowed_max_chain_length,0.0));	

	vector<double> gen_theta_sigma_sim(nr_of_sets_of_random_chains,0.0);


	cout << "You have selected " << random_chains <<  " (0 for exp. data, 1 means simulated chains)" <<endl;

	//Create histograms
#include "histograms.cxx"


	//Create smeared energy functions
	//#include "energy_functions.cxx"


	//Short chains pre-calc of lifetimes, excluding one chain
	// #include "short_chains_pre_calc.cxx"


	//Make sure the arrays and histos are emptied after the first readin
	//#include "empty_and_reset_arrays_and_histos.cxx"
	//cout << "funkade hit" << endl;


	//Initialisations needed for energy_calc
#include "Energy_calc_part0.cxx"

	//Read in chains and collect info
	for(int f = 1; f <= maximum_nr_of_chains; f++){

		if(f%10000 == 0) {cout << "f is now, in loop 1, " << f << endl;} 

		//Select only certain chains

		if(random_chains || std::find(std::begin(chains_to_consider), std::end(chains_to_consider),f) != std::end(chains_to_consider)){

			//Create the appropriate filename
			filename = path + "chain" + to_string(f) + ".txt";

			//Read in data     
			readin(filename);

			//Collect some info regarding the data set; times, theta, max_time 
			for (int iStep = 0; iStep < max_chain_length; iStep++){ 
				if(use_event(iStep,f)){
					time_avg[iStep] += all_chains[f][9+iStep*3];
					theta_avg[iStep] += log(all_chains[f][9+iStep*3]);
					time_max[iStep] = max(time_max[iStep], all_chains[f][9+iStep*3]);
				}	
			}    

			//For simulated sets of chains: collect the average time for each set
			if (random_chains && ind_tbar_param){
				for(int iStep = 0; iStep < max_chain_length; iStep++){
					SimAvgTimes[index][iStep] += all_chains[f][9+iStep*3];
					if (all_chains[f][9+iStep*3] > 0) {SimAvgThetas[index][iStep] += log(all_chains[f][9+iStep*3]);}
				}
				if (f % nr_of_chains_in_set == 0){  
					index++; //Increate index; index is the ID for the set of simulated chains
				}
			}

			//Energy stuff	
#include "Energy_calc_part1.cxx"

		} //Now, the selected chain has been read into the all_chains array

	} //Ends the first loop over f; arrays have been filled and sums have been collected 



	//Calculate average time using plain average (superior!)
	if(random_chains && ind_tbar_param){ 
		for (index = 0; index < nr_of_sets_of_random_chains; index++){
			for(int i = 0; i < max_chain_length; i++){
				SimAvgTimes[index][i] /= nr_in_step[i];
				SimAvgThetas[index][i] /= nr_in_step[i];
			}
		}
	}

	//Check number of times filled for each step, and transfer to arrays
	for(int iStep = 0; iStep < max_chain_length; iStep++){	 
		integrall[iStep] = h_decay_time[iStep]->Integral();
	}

	//Calculate and print averages for times and thetas
	for(int iStep = 0; iStep < max_chain_length; iStep++){
		time_avg[iStep] /= integrall[iStep];
		theta_avg[iStep] /= integrall[iStep];
		error_up[iStep] = log(2)*time_avg[iStep]/(1.0-1.0/sqrt(integrall[iStep]))-log(2)*time_avg[iStep];
		error_down[iStep] = log(2)*time_avg[iStep]-log(2)*time_avg[iStep]/(1.0+1.0/sqrt(integrall[iStep]));
		cout << endl << "The plain average HALFLIFE for step " << iStep << " is " << log(2)*time_avg[iStep] << " +" << error_up[iStep] << " -"<< error_down[iStep] << endl;
		cout << endl << "(The plain average lifetime for step " << iStep << "  is " << time_avg[iStep] <<  " and the number of chains is " << integrall[iStep] << ")" << endl << endl;
	}

	//Possibly, use Fritz' lifetime calculations
#include "various_lifetime_calc_Fritz_and_fits.cxx"


	//Here, decide what times and numbers of chains to be used in the FoM calculations. 
	//Depends on external/internal reference and
	//Exp. data/simluated chains 
	//Exp. data

	for(int i = 0; i < max_chain_length; i++){	

		if(!random_chains){
			if(!external_reference){
				time_fom[i] = time_avg[i];
				n_fom[i] = nr_in_step[i];
			}
			else {
				time_fom[i] = ref_halflife[i]/log(2);
				n_fom[i] = ref_nr_in_step[i];
			}
		}

		//For random chains
		if(random_chains){
			if(!external_reference){
				time_fom[i] = ref_halflife[i]/log(2);
				n_fom[i] = nr_in_step[i];
			}
			else {
				time_fom[i] = ref_halflife[i]/log(2);
				n_fom[i] = ref_nr_in_step[i];
			}
		}
	}




	index = 0;
	//Make a new loop over f, and restrict it to the same f as before
	for(int f = 1; f <= maximum_nr_of_chains; f++){


		if(f%10000 == 0) {cout << "f is now, in loop 2, " << f << endl;} //Print out progress

		if(random_chains || std::find(std::begin(chains_to_consider), std::end(chains_to_consider),f) != std::end(chains_to_consider)){


		  //Possibly, at some point, we want to to the flat-top FoM instead
		  //#include "FoM_up_and_low_lim.cxx"
		  
	
		  //Calculate FoM_smeared for each event
		  for (int iStep = 0; iStep < max_chain_length; iStep++){ 
		    if(use_event(iStep,f)){                          //Test what happens if time_fom -> SimAvgTimes ???
		     
		      //if(random_chains) FoM_smeared[iStep] = calc_FoM_smeared(n_fom[iStep], SimAvgTimes[index][iStep], all_chains[f][9+iStep*3]); //test,makes sense for internal refereces... best? I don't know! Actually, it depends. 12March2016: Use time_fom if you want to do the same as in the article on short chains
		    
		      if(random_chains) FoM_smeared[iStep] = calc_FoM_smeared(n_fom[iStep], time_fom[iStep], all_chains[f][9+iStep*3]); //test,makes sense for internal refereces... best? I don't know! Actually, it depends. 12March2016: Use time_fom if you want to do the same as in the article on short chains
		     
		      if(!random_chains) FoM_smeared[iStep] = calc_FoM_smeared(n_fom[iStep], time_fom[iStep], all_chains[f][9+iStep*3]); //good

		      if(FoM_smeared[iStep] < 0){
			cout << "This should NOT happen! " << endl; 
		      }
		    }
		    else{FoM_smeared[iStep] = 0.0;}	
		  }

		  
		  //Calculate the geometric mean of the FoMs in a chain
		  FoM_geom_smeared = 1.0;
		  int counter = 0;
		  for (int iStep = 0; iStep < max_chain_length; iStep++){
		    if (FoM_smeared[iStep] > 0){
		      FoM_geom_smeared *= FoM_smeared[iStep];
		      counter++;

		   
														  
		    }
		  }
		  if (counter == 0){ 
		    FoM_geom_smeared = 0.0; 
		    cout << "All FoM were 0!!!!!!" << endl << endl << endl;
		  }
		  else{
		    FoM_geom_smeared = pow(FoM_geom_smeared,1.0/counter);
		  }	  
	       		  
		  //Calculate average over the data set	  
		  FoM_smeared_average += FoM_geom_smeared;
	
		  //testing testing
		
		  //to_file_2 << 	pow(FoM_smeared[0]*FoM_smeared[1],1.0/2.0) << endl;	
	  
		  

		  //cout << "AAAAAAAAAAAAAARRRRRRRRRRRRRRRRGGGGGGGGGGGGGHHHHHHHHHHHHH! check the theta_sigma_tempsum!" << endl;

		  //Calculate Schmidt sums
		  for (int iStep = 0; iStep < max_chain_length; iStep++){ 
		    if(use_event(iStep,f)){
		      if(random_chains) {theta_sigma_tempsum[iStep] = theta_sigma_tempsum[iStep] + pow((log(all_chains[f][9+iStep*3])-SimAvgThetas[index][iStep]),2);} //This it the way! for RANDOM CHAINS!
		      if(!random_chains)theta_sigma_tempsum[iStep] = theta_sigma_tempsum[iStep] + pow((log(all_chains[f][9+iStep*3])-theta_avg[iStep]),2); //previous, stupid, way, but is the right for EXPERIMENTAL CHAINS
		    }	
		  }
		  
		  
		  //cout << "AAAAAAAAAAAAAARRRRRRRRRRRRRRRRGGGGGGGGGGGGGHHHHHHHHHHHHH! check the gen_theta_sigma_tempprod!" << endl;	

		  //Calculate generalised Schmidt sums
		  gen_theta_sigma_tempprod = 1.0;
		  counter = 0;
		  for (int iStep = 0; iStep < max_chain_length; iStep++){ 
		    if(use_event(iStep,f)){
		      //cout << "simavgtheta " << SimAvgThetas[index][iStep] << " index " << index << " iStep is " << iStep << endl;
		      if(random_chains) {gen_theta_sigma_tempprod *= pow((log(all_chains[f][9+iStep*3])-SimAvgThetas[index][iStep]),2);} //this is the way! for RANDOM CHAINS!
		      if(!random_chains) {gen_theta_sigma_tempprod *= pow((log(all_chains[f][9+iStep*3])-theta_avg[iStep]),2);} //previous, stupid, way, but works for EXPERIMENT!
		      counter++;                          
		    }
		  }
		  if (counter == 0){ 
		    gen_theta_sigma_tempprod = 0.0; 
		    cout << "One chain seems to be missing?" << endl << endl << endl;
		  }
		  else{
		    gen_theta_sigma_tempprod = pow(gen_theta_sigma_tempprod,1.0/counter);
		  }
		  
		  gen_theta_sigma += gen_theta_sigma_tempprod;
		  


		  
		  
		  //If we use random chains, the data needs to be stored for each SETof chains 
		  if(random_chains){		    
		    
		    // Collect ALL FoMs, and geometric averages. Use these for plotting the expected values for one/two/three etc. FoM values.
		    
		    for (int iStep = 0; iStep < max_chain_length; iStep++){
		      FoMSmearedSim[index][(f-1)%nr_of_chains_in_set][iStep] = FoM_smeared[iStep];

		
		    }
		    FoM_smeared_sim_geom[index][(f-1)%nr_of_chains_in_set] = FoM_geom_smeared; 
		    
		    //Calculate average FoM smeared   
		    for (int iStep = 0; iStep < max_chain_length; iStep++){
		      FoM_sim_smeared_avg[index][iStep] += FoM_smeared[iStep];  
		    }
		    FoM_smeared_sim_geom_avg[index] += FoM_geom_smeared;
		    



		    /*
		cout << "Temporary stff lines 415 etc." << endl;
		cout << f << "  ";
		for (int iStep = 0; iStep < max_chain_length; iStep++){
		  print_FoM_smeared(FoM_smeared[iStep]);
		}
		    */

		  


		    //Store Schmidt values (original test; one step at t)
		    for (int iStep = 0; iStep < max_chain_length; iStep++){
		      theta_sigma_sim[index][iStep] += FoM_smeared[iStep];                 //WTF?????????????????????????????????
		    }
		    
		    //Increase index and save the generalised Schmidt value
		    if (f % nr_of_chains_in_set == 0) {
		      gen_theta_sigma_sim[index] = pow(gen_theta_sigma/nr_of_chains_in_set,1.0/2.0);
		      gen_theta_sigma = 0;	
		      for (int iStep = 0; iStep < max_chain_length; iStep++){
			theta_sigma_sim[index][iStep] = pow(theta_sigma_tempsum[iStep]/(integrall[iStep]/nr_of_sets_of_random_chains),1.0/2.0);
			theta_sigma_tempsum[iStep] = 0;				 
		      }
		      index++; 
		    }
		    
		  }//ends "if (random chains)"
		  
		  
		  /* //WTF does this one do?
		  //Copy over spectra 	
		  if(real_chains){
		  pic1 = (TF1*)norm_gf_ref_pdf_logbins->Clone("save_to_pic1"); 
		  picpic1 = new TF1("sth1","save_to_pic1",log_lowlim, log_hilim);
		  pic2 = (TF1*)norm_gf_ref_pdf_logbins->Clone("save_to_pic2"); 
		  picpic2 = new TF1("sth2","save_to_pic2",log_lowlim, log_hilim);
		  pic3 = (TF1*)norm_gf_ref_pdf_logbins->Clone("save_to_pic3"); 
		  picpic3 = new TF1("sth3","save_to_pic3",log_lowlim, log_hilim);
		  }
		  */
		  
		  
		  //Type out the "smeared" Figure-of-Merits for experimental data
		  if(!random_chains && print_smeared_FoM){
		    
		    //Type out some useful info (this sometimes does not work if, e.g.,1101 is excluded)
		    if(f%100-1 == 0) {cout << endl << endl;} 
		    if(f == 1001){cout << "Dubna 3n" << endl;}
		    if(f == 1101){cout << "Dubna short" << endl;}
		    if(f == 1201){cout << "Dubna 4n" << endl;}
		    if(f == 1301){cout << "Lund 3n" << endl;}
		    if(f == 1401){cout << "Lund short" << endl;}
		    if(f == 1501){cout << "Lund 4n" << endl;}
		    if(f == 1601){cout << "Berkeley 3n" << endl;}
		    if(f == 1701){cout << "Berkeley short" << endl;}
		    
		    
		    cout << f << "  ";
		    for (int iStep = 0; iStep < max_chain_length; iStep++){
		      print_FoM_smeared(FoM_smeared[iStep]);
		    }
		    
		    
		    //Print geometric average over the chain
		    cout << fixed << setprecision(3);      
		    cout << setw(7) << "& " << FoM_geom_smeared << "  &  $+$ & $+$ \\\\ " << endl;
		    
		    //Restore precision
		    cout << fixed << setprecision(6); 
		    
		  } //Ends "Type out the "smeared" Figure-of-Merits"  
		   
		  
		} //Ends loop over the selected chain 
		
	} //Ends loop 2 over chains!


	cout << "We are out of loop 2" << endl;

	//Print out the amazing FoM for exp. data
	if(!random_chains){
		FoM_smeared_average /= nr_of_chains_in_set; 
		cout << "The fantastic FoM is " << FoM_smeared_average << endl;

		gen_theta_sigma = pow(gen_theta_sigma/nr_of_chains_in_set,1.0/2.0);
		cout << "The great generalised Schmidt value is " << gen_theta_sigma << endl;
	}


	//For random chains; fill histos, files, etc.
	if(random_chains){ 

		//Calculate average smeared FoM
		for (index = 0; index < nr_of_sets_of_random_chains; index++){
			for(int i = 0; i < max_chain_length; i++){	
				FoM_sim_smeared_avg[index][i] /= nr_in_step[i];
			}
			FoM_smeared_sim_geom_avg[index] /= nr_of_chains_in_set; 
		}

		//Print out the simulated FoM so that they can be plotted with another program !!!!!!!!!!!!!!!
		ofstream to_file_0("one_FoM_jn.txt",ios::out);		
		ofstream to_file_1("single_tresteg.txt",ios::out);		
		ofstream to_file_2("single_tresteg_2.txt",ios::out);		
		ofstream to_file_all("fourteen_tresteg.txt",ios::out);		
		for(index = 0; index < nr_of_sets_of_random_chains; index ++){
			to_file_0 << FoMSmearedSim[index][0][0] << endl;
			to_file_1 << FoM_smeared_sim_geom[index][1] << endl;
			to_file_2 << FoM_smeared_sim_geom[index][2] << endl;
			to_file_all << FoM_smeared_sim_geom_avg[index] << endl;
		}
		to_file_0.close();
		to_file_1.close();
		to_file_2.close();
		to_file_all.close();


		/*
		//Print out the simulated FoM so that they can be plotted with another program--- OLD!
		ofstream single_fom_2step_84_cp_84("single_FoM_2step_84_cp_84.txt",ios::out);		
		for(index = 0; index < nr_of_sets_of_random_chains; index ++){
			single_fom_2step_84_cp_84 << pow(FoMSmearedSim[index][10][0]*FoMSmearedSim[index][10][1],0.5) << endl;
			single_fom_2step_84_cp_84 << pow(FoMSmearedSim[index][11][0]*FoMSmearedSim[index][11][1],0.5) << endl;
			single_fom_2step_84_cp_84 << pow(FoMSmearedSim[index][12][0]*FoMSmearedSim[index][12][1],0.5) << endl;
		}
		single_fom_2step_84_cp_84.close();
		*/



		/*
	ofstream double_fom("avg_of_two_FoM_from_FoM_calc.txt",ios::out);		
	for(index = 0; index < nr_of_sets_of_random_chains; index ++){
	double_fom << (FoMSmearedSim[index][1][3]+FoMSmearedSim[index][2][3])/2.0 << endl;
	}
	double_fom.close();
		 */


		//Fill histograms
		for (index = 0; index < maximum_nr_of_chains/nr_of_chains_in_set; index++){    //maximum_nr_of_chains nr_of_sets_of_random_chains !!!!!!!!!!!!!!!!!
			for (int iStep = 0; iStep < max_chain_length; iStep++){ 
				h_FoM_smeared_avg[iStep]->Fill(FoM_sim_smeared_avg[index][iStep]);
				h_Schmidt[iStep]->Fill(theta_sigma_sim[index][iStep]);
			}
			h_FoM_smeared_MC->Fill(FoM_smeared_sim_geom_avg[index]);    //This is the correct way //WROOOOOONG
			h_Schmidt_gen->Fill(gen_theta_sigma_sim[index]);
			//h_FoM_smeared_MC->Fill(pow(FoM_sim_smeared_average[index][0]*FoM_sim_smeared_average[index][1]*FoM_sim_smeared_average[index][2],1.0/3.0)); //TEST. JACKIE DOES THIS???   

		}

		//Find upper and lower 5% and 1% limits on simulated final FoM values (geom+avg)

		find_conf_limits(h_FoM_smeared_MC);
		//find_conf_limits(h_Schmidt_gen);



	


	}//Ends if(random_chains)



	//Calculate Schmidt values and type out to screen
	if(!random_chains){
	  for(int iStep = 0; iStep < max_chain_length; iStep++){
	    theta_sigma[iStep] = sqrt(theta_sigma_tempsum[iStep]/integrall[iStep]);  
	    cout << "Theta sigma is  " << theta_sigma[iStep] << "for step " << iStep << " and integral is " << integrall[iStep] << endl;
	  }
	}


	cout << endl << endl;

	for(int iStep = 0; iStep < max_chain_length; iStep++){
	  cout << " & " << log(2)*time_avg[iStep] << " & " << (int) round(integrall[iStep]);
	}

	cout << endl << endl;


	//Create some fun functions
	TF1 *pdf_logbins_1 = new TF1("pdf_logbins_1","[1]*x/[0]*exp(-x/[0])",log_lowlim,log_hilim);
	pdf_logbins_1->SetParameter(0,time_avg[0]);
	pdf_logbins_1->SetParameter(1,10);

	TF1 *pdf_logbins_1_l = new TF1("pdf_logbins_1_l","[1]*x/[0]*exp(-x/[0])",log_lowlim,log_hilim);
	pdf_logbins_1_l->SetParameter(0,time_avg[0]/5.0);
	pdf_logbins_1_l->SetParameter(1,10);

	TF1 *pdf_logbins_1_h = new TF1("pdf_logbins_1_h","[1]*x/[0]*exp(-x/[0])",log_lowlim,log_hilim);
	pdf_logbins_1_h->SetParameter(0,time_avg[0]*5.0);
	pdf_logbins_1_h->SetParameter(1,10);


	TF1 *pdf_logbins_2 = new TF1("pdf_logbins_2","x/[0]*exp(-x/[0])",log_lowlim,log_hilim);
	pdf_logbins_2->SetParameter(0,time_avg[1]);
	
	TF1 *pdf_logbins_3 = new TF1("pdf_logbins_3","x/[0]*exp(-x/[0])",log_lowlim,log_hilim);
	pdf_logbins_3->SetParameter(0,time_avg[2]);

	TF1 *pdf_lnt_1 = new TF1("pdf_logbins_3","[1]*exp(x)/[0]*exp(-exp(x)/[0])",log(log_lowlim),log(log_hilim));
	pdf_lnt_1->SetParameter(0,time_avg[0]);
	pdf_lnt_1->SetParameter(1,10);

	TF1 *pdf_lnt_1_l = new TF1("pdf_logbins_3_l","[1]*exp(x)/[0]*exp(-exp(x)/[0])",log(log_lowlim),log(log_hilim));
	pdf_lnt_1_l->SetParameter(0,time_avg[0]/5.0);
	pdf_lnt_1_l->SetParameter(1,10);

	TF1 *pdf_lnt_1_h = new TF1("pdf_logbins_3_h","[1]*exp(x)/[0]*exp(-exp(x)/[0])",log(log_lowlim),log(log_hilim));
	pdf_lnt_1_h->SetParameter(0,time_avg[0]*5.0);
	pdf_lnt_1_h->SetParameter(1,10);



	TF1 *pdf_smeared_logbins_1 = new TF1("pdf_smeared_logbins_1","x*([1]-1)*pow([1]*[0],([1]-1))/pow(([1]*[0]+x),[1])",log_lowlim,log_hilim); 
	pdf_smeared_logbins_1->SetParameter(0,time_avg[0]);
	pdf_smeared_logbins_1->SetParameter(1,nr_in_step[0]);
	pdf_smeared_logbins_1->SetLineColor(4);





	double norm[max_chain_length] = {0.0};
	//Normalise histos to compare with functions
	for(int iStep = 0; iStep < max_chain_length; iStep++){
	  for(int i = 0; i < nr_of_logbins; i++){
	    norm[iStep] += h_decay_time_logbins[iStep]->GetBinContent(i)*weight; 
	  }
	  for(int i = 0; i < nr_of_logbins; i++){
	    //h_decay_time_logbins[iStep]->SetBinContent(i,h_decay_time_logbins[iStep]->GetBinContent(i)/norm[iStep]); //Rigth now, don't
	  }
	}
	//cout << "weight is " << weight << " and norm is " << norm << endl;	




	//Make plots of times, energies, FoMs etc.
	if(plot_a_lot){ 



	  TCanvas *MyCanvas_times = new TCanvas("MyCanvas_times");
	  MyCanvas_times->Divide(1,1); 
	  MyCanvas_times->cd(1);
	  gPad->SetLogx();

	  h_decay_time_logbins[0]->SetTitle("");
	  h_decay_time_logbins[0]->SetStats(0);
	  h_decay_time_logbins[0]->GetXaxis()->SetTitle("t"); // #xi_{m,n,l}");
	  h_decay_time_logbins[0]->GetYaxis()->SetTitle("counts per bin");
	  h_decay_time_logbins[0]->GetXaxis()->SetTitleOffset(1.2);
	  h_decay_time_logbins[0]->GetYaxis()->SetTitleOffset(1.0);
	  h_decay_time_logbins[0]->GetXaxis()->CenterTitle();
	  h_decay_time_logbins[0]->GetYaxis()->CenterTitle();
	  h_decay_time_logbins[0]->GetXaxis()->SetRangeUser(0.002,4);
	  h_decay_time_logbins[0]->GetYaxis()->SetRangeUser(0,6);
	  h_decay_time_logbins[0]->GetYaxis()->SetNdivisions(007);
	  h_decay_time_logbins[0]->GetYaxis()->SetDecimals(0);
	  
	  h_decay_time_logbins[0]->SetLineWidth(2);
	  h_decay_time_logbins[0]->Draw();
	  pdf_logbins_1->SetLineColor(1);
	  pdf_logbins_1->Draw("same");
	
	  pdf_logbins_1_l->SetLineColor(2);  
	  pdf_logbins_1_l->Draw("same");
	

	  pdf_logbins_1_h->SetLineColor(3);
	  pdf_logbins_1_h->Draw("same");

	  TLegend *leg = new TLegend(0.20,0.65,0.35,0.85);
	  //leg->AddEntry(h_decay_time_logbins[0], "stuff", "l");
	  leg->AddEntry(pdf_logbins_1_l, "#tau = 0.24/5 s", "l");
	  leg->AddEntry(pdf_logbins_1, "#tau = 0.24 s", "l");
	  leg->AddEntry(pdf_logbins_1_h, "#tau = 0.24*5 s", "l");
	  leg->SetFillStyle(0);
	  leg->SetTextSize(0.046);

	  leg->Draw("same");


	  MyCanvas_times->Print("f_decay_time_logbins_and_fn.pdf");   


	  TCanvas *MyCanvas_times2 = new TCanvas("MyCanvas_times2");
	  MyCanvas_times2->Divide(1,1); 
	  MyCanvas_times2->cd(1); 

	  h_decay_time_ln[0]->SetTitle("");
	  h_decay_time_ln[0]->SetStats(0);
	  h_decay_time_ln[0]->GetXaxis()->SetTitle("ln(t)"); // #xi_{m,n,l}");
	  h_decay_time_ln[0]->GetYaxis()->SetTitle("counts per bin");
	  h_decay_time_ln[0]->GetXaxis()->SetTitleOffset(1.2);
	  h_decay_time_ln[0]->GetYaxis()->SetTitleOffset(1.0);
	  h_decay_time_ln[0]->GetXaxis()->CenterTitle();
	  h_decay_time_ln[0]->GetYaxis()->CenterTitle();
	  h_decay_time_ln[0]->GetXaxis()->SetRangeUser(-6.214,1.386);
	  h_decay_time_ln[0]->GetYaxis()->SetRangeUser(0,6);
	  h_decay_time_ln[0]->GetYaxis()->SetNdivisions(007);
	  h_decay_time_ln[0]->GetYaxis()->SetDecimals(0);

	  h_decay_time_ln[0]->SetLineWidth(2);
	  h_decay_time_ln[0]->Draw();
	  pdf_lnt_1->SetLineColor(1);
	  pdf_lnt_1->Draw("same");
	  pdf_lnt_1_l->SetLineColor(2);
	  pdf_lnt_1_l->Draw("same");
	  pdf_lnt_1_h->SetLineColor(3);
	  pdf_lnt_1_h->Draw("same");

	  TLegend *leg2 = new TLegend(0.20,0.65,0.35,0.85);
	  //leg2->AddEntry(h_decay_time_logbins[0], "kajshd", "l");
	  leg2->AddEntry(pdf_logbins_1_l, "#tau = 0.24/5 s", "l");
	  leg2->AddEntry(pdf_logbins_1, "#tau = 0.24 s", "l");
	  leg2->AddEntry(pdf_logbins_1_h, "#tau = 0.24*5 s", "l");
	  leg2->SetFillStyle(0);
	  leg2->SetTextSize(0.046);

	  leg2->Draw("same");	


  MyCanvas_times2->Print("f_decay_time_ln.pdf");




	  TCanvas *MyCanvas2 = new TCanvas("MyCanvas2");
	  MyCanvas2->Divide(1,3); 

	  MyCanvas2->cd(1);
	  gPad->SetLogx();
	  h_decay_time_logbins[0]->Draw();
	  pdf_logbins_1->Draw("same");
	  pdf_smeared_logbins_1->Draw("same");


	  MyCanvas2->cd(2);
	  gPad->SetLogx();
	  h_decay_time_logbins[1]->Draw();
	  pdf_logbins_2->Draw("same");

	  MyCanvas2->cd(3);
	  gPad->SetLogx();
	  h_decay_time_logbins[2]->Draw();
	  pdf_logbins_3->Draw("same");
	  
	  MyCanvas2->Print("times2.pdf");   



	  TCanvas *MyCanvas3 = new TCanvas("MyCanvas3");
	  MyCanvas3->Divide(1,2); 

	  MyCanvas3->cd(1);
	  h_FoM_smeared_MC->Draw();

	  MyCanvas3->cd(2);
	  h_Schmidt_gen->Draw();

	  MyCanvas3->Print("FoM_and_genSchmidt.pdf");   




	  TCanvas *MyCanvas = new TCanvas("MyCanvas");
	  MyCanvas->Divide(3,4); 
	  
#include "Energy_calc_part2.cxx"
	  
	  
	  MyCanvas->cd(1);
	  gPad->SetLogx();
	  h_decay_time_logbins[0]->Draw();
	  pdf_logbins_1->Draw("same");
	  
	  
	  MyCanvas->cd(2);
	  gPad->SetLogx();
	  h_decay_time_logbins[1]->Draw();
	  pdf_logbins_2->Draw("same");
	  //picpic2->Draw("same");
	  ofstream times_2("times_2_from_FoM_calc.txt",ios::out);		
	  for(int t = 0; t < 2600; t++){
	    times_2 << h_decay_time_logbins[1]->GetBinContent(t)<< endl;
		}
	  times_2.close();
	  
	  MyCanvas->cd(3);
	  gPad->SetLogx();
	  h_decay_time_logbins[2]->Draw();
	  pdf_logbins_1->Draw("same");
	  //picpic3->Draw("same");
	  ofstream times_3("times_3_from_FoM_calc.txt",ios::out);		
	  for(int t = 0; t < 2600; t++){
	    times_3 << h_decay_time_logbins[2]->GetBinContent(t)<< endl;
	  }
	  times_3.close();     
	  
	  MyCanvas->cd(4);
	  h_FoM_smeared_avg[0]->Draw();
	  ofstream fom_1("fom_1_FoM_calc.txt",ios::out);		
	  for(int t = 0; t < 500; t++){
	    fom_1 <<  h_FoM_smeared_avg[0]->GetBinContent(t)<< endl;
	  }
	  fom_1.close();      
	  
	  MyCanvas->cd(5);
	  h_FoM_smeared_avg[1]->Draw();
	  ofstream fom_2("fom_2_FoM_calc.txt",ios::out);		
	  for(int t = 0; t < 500; t++){
	    fom_2 <<  h_FoM_smeared_avg[1]->GetBinContent(t)<< endl;
	  }
	  fom_2.close();
	  
	  MyCanvas->cd(6);
	  h_FoM_smeared_avg[2]->Draw();
	  ofstream fom_3("fom_3_FoM_calc.txt",ios::out);		
	  for(int t = 0; t < 500; t++){
	    fom_3 <<  h_FoM_smeared_avg[2]->GetBinContent(t) << endl;
	  }
	  fom_3.close();   
	  
	  MyCanvas->cd(7);
	  h_FoM_smeared_MC->Draw();
	  ofstream fom_tot("fom_tot_FoM_calc.txt",ios::out);		
	  for(int t = 0; t < 500; t++){
	    fom_tot <<  h_FoM_smeared_MC->GetBinContent(t)<< endl;
	  }
	  fom_tot.close();
	  
	  MyCanvas->cd(8);
	  h_Schmidt[0]->Draw();
	  
	  MyCanvas->cd(9);
	  h_Schmidt[1]->Draw();
	  
	  MyCanvas->cd(10);
	  h_Schmidt[2]->Draw();
	  
	  
	  MyCanvas->cd(11);
	  h_Schmidt_gen->Draw();
	  
	  
	  MyCanvas->Print("outputspec.pdf");   
	  
	}



	cout << "Program finished!" << endl;
	return 0;

} //Ends main function


#include "functions.cxx"





//PIECES OF CODE THAT ARE NOT CURRENTLY USED

/*
  //Method 1. Calculate overlap integral.
  cout << "METHOD 1" << endl;

  double overlap1 = 0;
  double overlap2 = 0;
  double overlap3 = 0;
  double overlap_tot = 0;

  overlap1 = overlap(halflife_ref[0], avgtime_1);

  overlap2 = overlap(halflife_ref[1], avgtime_2);

  if(no_of_decays == 3) overlap3 = overlap(halflife_ref[2], avgtime_3);

  overlap_tot = overlap1*overlap2;
  cout << "Product if only two decays  "  << overlap_tot << endl; 
  if(no_of_decays == 3){overlap_tot = overlap_tot*overlap3;
    overlap_tot = pow(overlap_tot,1.0/3.0);}
  else overlap_tot = sqrt(overlap_tot);  

  cout << "Overlaps are " << overlap1 << "  " << overlap2 << "   " << overlap3 << "  and total =  "  << overlap_tot <<endl;


  //Method 2. P-värdet
  cout << "METHOD 2" << endl;

  //Create reference functions based on the references
  TF1 *decay_fref_1 = new TF1("decay_fref_1","[0]*exp(-[0]*x)",0,100);
  decay_fref_1->SetParameter(0,log(2)/halflife_ref[0]);
  decay_fref_1->SetNpx(1000);
  TF1 *decay_fref_2 = new TF1("decay_fref_2","[0]*exp(-[0]*x)",0,100);
  decay_fref_2->SetParameter(0,log(2)/halflife_ref[1]);
  decay_fref_2->SetNpx(1000);
  TF1 *decay_fref_3 = new TF1("decay_fref_3","[0]*exp(-[0]*x)",0,100);
  decay_fref_3->SetParameter(0,log(2)/halflife_ref[2]);
  decay_fref_3->SetNpx(1000);

  double P_value_1;
  double P_value_2;
  double P_value_3;
  if(avgtime_1 > halflife_ref[0]) {P_value_1 = decay_fref_1->Integral(avgtime_1,100);}
  else  {P_value_1 = decay_fref_1->Integral(0,avgtime_1);}

  if(avgtime_2 > halflife_ref[1]) {P_value_1 = decay_fref_2->Integral(avgtime_2,100);}
  else  {P_value_2 = decay_fref_2->Integral(0,avgtime_2);}

  if(no_of_decays == 3){
  if(avgtime_3 > halflife_ref[2]) {P_value_3 = decay_fref_3->Integral(avgtime_3,100);}
  else  {P_value_3 = decay_fref_3->Integral(0,avgtime_3);}
  }

  cout << "P-value 1 is " << P_value_1 << endl;
  cout << "P-value 2 is " << P_value_2 << endl;
  if(no_of_decays == 3) {cout << "P-value 3 is " << P_value_3 << endl;}
  //Tänk och läs om minsta och största värde
  //decay_fref_1->Draw();
 */

/*
  //Method 3. Likelihood-function
  cout << "METHOD 3" << endl;

  if(no_of_decays == 3){
    TF1 *likelihood_function = new TF1("likelihoodfunction","[0]*exp(-[0]*[1])*[2]*exp(-[2]*[3])*[4]*exp(-[4]*[5])/([0]*[2]*[4])",0,100);
    likelihood_function->SetParameters(log(2)/halflife_ref[0],avgtime_1,log(2)/halflife_ref[1],avgtime_2,log(2)/halflife_ref[2],avgtime_3); //Normalizes so t_m_1,2,3 = 0 gives 1
    cout << "Value of likelihood function for three decays is " <<  likelihood_function->Eval(1) << endl;
  } 

  if(no_of_decays == 2){
    TF1 *likelihood_function = new TF1("likelihoodfunction","[0]*exp(-[0]*[1])*[2]*exp(-[2]*[3])/([0]*[2])",0,100);//Normalizes so t_m_1,2 = 0 gives 1
    likelihood_function->SetParameters(log(2)/halflife_ref[0],avgtime_1,log(2)/halflife_ref[1],avgtime_2);
    cout << "Value of likelihood function for two decays is " <<  likelihood_function->Eval(1) << endl;
  }
 */

//Weird; likelihood function is largest if all measured times are close to zero. Not good measure!

//Method 3.1. Work with ln(t), then the likelihood function takes the form

//cout << "METHOD 3.1" << endl;




//For a flat-top FoM
/*    if(avgtime_1 >= halflife_ref_low[0]/log(2) && avgtime_1 <= halflife_ref_high[0]/log(2)){
      s[0] = 100;
    } 
    else if(avgtime_1 < halflife_ref_low[0]/log(2)){ 
      likelihood_function_LN_step1->SetParameters(log(2)/halflife_ref_low[0],avgtime_1);
      s[0] = 100*(likelihood_function_LN_step1->Eval(1));
    }
    else if(avgtime_1 > halflife_ref_high[0]/log(2)){
      likelihood_function_LN_step1->SetParameters(log(2)/halflife_ref_high[0],avgtime_1);
      s[0] = 100*(likelihood_function_LN_step1->Eval(1));
    }
    else {cout << "Something wrong!" << endl;}


    if(avgtime_2 >= halflife_ref_low[1]/log(2) && avgtime_2 <= halflife_ref_high[1]/log(2)){
      s[1] = 100;
    } 
    else if(avgtime_2 < halflife_ref_low[1]/log(2)){ 
      likelihood_function_LN_step2->SetParameters(log(2)/halflife_ref_low[1],avgtime_2);
      s[1] = 100*(likelihood_function_LN_step2->Eval(1));
    }
    else if(avgtime_2 > halflife_ref_high[1]/log(2)){
      likelihood_function_LN_step2->SetParameters(log(2)/halflife_ref_high[1],avgtime_2);
      s[1] = 100*(likelihood_function_LN_step2->Eval(1));
    }
    else {cout << "Something wrong!" << endl;}


    if(avgtime_3 >= halflife_ref_low[2]/log(2) && avgtime_3 <= halflife_ref_high[2]/log(2)){
      s[2] = 100;
    } 
    else if(avgtime_3 < halflife_ref_low[2]/log(2)){ 
      likelihood_function_LN_step3->SetParameters(log(2)/halflife_ref_low[2],avgtime_3);
      s[2] = 100*(likelihood_function_LN_step3->Eval(1));
    }
    else if(avgtime_3 > halflife_ref_high[2]/log(2)){
      likelihood_function_LN_step3->SetParameters(log(2)/halflife_ref_high[2],avgtime_3);
      s[2] = 100*(likelihood_function_LN_step3->Eval(1));
    }
    else {cout << "Something wrong!" << endl;}
 */
/*
  bool draw_ln_spectra = 0;
  if(draw_ln_spectra == 1){
  h_decay_time_ln[0]->SetLineWidth(3);  
  h_decay_time_ln[1]->SetLineWidth(3);  
  h_decay_time_ln[2]->SetLineWidth(3);  
  h_decay_time_ln[3]->SetLineWidth(3);  
  h_decay_time_ln[4]->SetLineWidth(3);  
  h_decay_time_ln[5]->SetLineWidth(3);  

  h_decay_time_ln[1]->SetLineColor(2);  
  h_decay_time_ln[2]->SetLineColor(3);  
  h_decay_time_ln[3]->SetLineColor(4);  
  h_decay_time_ln[4]->SetLineColor(5);  
  h_decay_time_ln[5]->SetLineColor(6);  

  h_decay_time_ln[0]->Draw();  
  h_decay_time_ln[1]->Draw("same");  
  h_decay_time_ln[2]->Draw("same");  
  h_decay_time_ln[3]->Draw("same");  
  h_decay_time_ln[4]->Draw("same");  
  h_decay_time_ln[5]->Draw("same");  
  }
 */




/*
  //Type in values (only if ask = 1)
  if(type_in_values){
    cout << endl;
    if(ask){
      cout << "halflife_ref[0] = "; 
      cin >> halflife_ref[0];
      cout << endl;}
    cout << "avgtime_1 = "; 
    cin >> avgtime_1;
    cout << endl;
    if(ask){cout << "halflife_ref[1] = "; 
      cin >> halflife_ref[1];
      cout << endl;}
    cout << "avgtime_2 = "; 
    cin >> avgtime_2;
    cout << endl;
    if(no_of_decays == 3){  
      if(ask){cout << "halflife_ref[2] = "; 
	cin >> halflife_ref[2];
	cout << endl;}
      cout << "avgtime_3 = "; 
      cin >> avgtime_3; 
      cout << endl;
    }
  }
 */
