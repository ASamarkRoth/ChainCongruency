#include <iostream>
#include <string>
#include <sstream>
#include "TH1.h"
#include "TFile.h"
#include "TF1.h"
#include <fstream>
#include "TMath.h"
#include <iomanip>
#include "TCanvas.h"
#include "TAxis.h"

using namespace std;

//Define how to use te code:
bool ask = 0;
bool type_in_values = 0;
bool read_values_from_file = 1;

//Functions (defined below main())
double overlap(double halflife_ref, double avgtime);
void readin(string chainX);
void readinL(string chainX); //Read in Lund chains

//Variables
double halflife_ref_1;
double halflife_ref_2;
double halflife_ref_3;

double halflife_ref_1_low;
double halflife_ref_2_low;
double halflife_ref_3_low;
double halflife_ref_1_high;
double halflife_ref_2_high;
double halflife_ref_3_high;

double avgtime_1;
double avgtime_2;
double avgtime_3;
double s1;
double s2;
double s3;

int no_of_decays = 0;
int scenario;
int chain_number;
int m;

float all_chains[3000][25];

char filename[64];
char filename2[64];

//Spectra
TH1F* h_implant_energy;
TH1F* h_first_decay_energy;
TH1F* h_second_decay_energy;
TH1F* h_third_decay_energy;
TH1F* h_fourth_decay_energy;
TH1F* h_fifth_decay_energy;
TH1F* h_sixth_decay_energy;
TH1F* h_seventh_decay_energy;
TH1F* h_eigth_decay_energy;

TH1F* h_first_decay_time;
TH1F* h_second_decay_time;
TH1F* h_third_decay_time;
TH1F* h_fourth_decay_time; 
TH1F* h_fifth_decay_time;
TH1F* h_sixth_decay_time;
TH1F* h_seventh_decay_time;
TH1F* h_eigth_decay_time;

TH1F* h_first_ln_decay_time;
TH1F* h_second_ln_decay_time;
TH1F* h_third_ln_decay_time;
TH1F* h_fourth_ln_decay_time; 
TH1F* h_fifth_ln_decay_time;
TH1F* h_sixth_ln_decay_time;
TH1F* h_seventh_ln_decay_time;
TH1F* h_eigth_ln_decay_time;

TH1F* h_first_decay_time_logbins;
TH1F* h_second_decay_time_logbins;
TH1F* h_third_decay_time_logbins;
TH1F* h_fourth_decay_time_logbins;
TH1F* h_fifth_decay_time_logbins;
TH1F* h_sixth_decay_time_logbins;
TH1F* h_seventh_decay_time_logbins;
TH1F* h_eigth_decay_time_logbins;

TH1F* h1;



int main(){

  //Read in chains
  for(int f = 1001; f < 1002; f++){ 
    sprintf(filename,"chain%d.txt.newformat",f);
   
    readinL(filename);   

    cout << all_chains[0][0] << endl;

     
    //Now, construct new files
    sprintf(filename2,"chain%d.txt",f);
    ofstream chain2(filename2,ios::out);

    chain2<<all_chains[f][0]<<endl;  //ID
    chain2<<10<< endl;               //Beam energy?   
    chain2<<all_chains[f][8]<< endl; //Strip x
    chain2<<0<<endl;                 //Strip y 
    chain2<<0<<endl;                 //Pixel
    chain2<<all_chains[f][1]<< endl; //Imp. energy
    chain2<<0<< endl;                //Imp. time == 0
    chain2<<all_chains[f][2]<< endl; //First energy
    chain2<<all_chains[f][9]<< endl; //First time   
    chain2<<all_chains[f][3]<< endl; 
    chain2<<all_chains[f][10]<< endl;
    chain2<<all_chains[f][4]<< endl;
    chain2<<all_chains[f][11]<< endl;
    chain2<<all_chains[f][5]<< endl;
    chain2<<all_chains[f][12]<< endl;
    chain2<<all_chains[f][6]<< endl;
    chain2<<all_chains[f][13]<< endl;
    chain2<<all_chains[f][7]<< endl;
    chain2<<all_chains[f][14]<< endl;

    chain2.close();


  } //Ends loop over chains


  return 0;

} //Ends main function


//Routine to read in Lund chains
void readinL(string chainX){
  Int_t m = 0;
  Int_t chain_number;
  Float_t temp = 0;
  ifstream chain(chainX.c_str(),ios::in);
  while (chain>>temp){
    if (m==0) {
      chain_number = temp;
      all_chains[chain_number][m] = temp;
      m++;
    } 
    else if (m==1) {all_chains[chain_number][m] = temp; m++;}
    else if (m==2) {all_chains[chain_number][m] = temp; m++;} 
    else if (m==3) {all_chains[chain_number][m] = temp; m++;}
    else if (m==4) {all_chains[chain_number][m] = temp; m++;}
    else if (m==5) {all_chains[chain_number][m] = temp; m++;}
    else if (m==6) {all_chains[chain_number][m] = temp; m++;}      
    else if (m==7) {all_chains[chain_number][m] = temp; m++;}
    else if (m==8) {all_chains[chain_number][m] = temp; m++;}
    else if (m==9) {all_chains[chain_number][m] = temp; m++;}
    else if (m==10) {all_chains[chain_number][m] = temp; m++;}
    else if (m==11) {all_chains[chain_number][m] = temp; m++;}
    else if (m==12) {all_chains[chain_number][m] = temp; m++;}
    else if (m==13) {all_chains[chain_number][m] = temp; m++;}
    else if (m==14) {all_chains[chain_number][m] = temp; m++;}
    else if (m==15) {all_chains[chain_number][m] = temp; m++;}
    else if (m==16) {all_chains[chain_number][m] = temp; m++;}
    else if (m==17) {all_chains[chain_number][m] = temp; m++;}
    else if (m==18) {all_chains[chain_number][m] = temp; m++;}
    else if (m==19) {all_chains[chain_number][m] = temp; m++;}
    else if (m==20) {all_chains[chain_number][m] = temp; m++;}

  }
  chain.close();
}


