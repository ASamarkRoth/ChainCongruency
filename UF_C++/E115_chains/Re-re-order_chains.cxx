#include <iostream>
#include <string>
#include <sstream>


using namespace std;


void readinL(string chainX); //Read in chains
float all_chains[3000][25];
char filename[64];
char filename2[64];

int main(){

  //Read in chains
  for(int f = 1601; f <= 1643; f++){ 

    sprintf(filename,"Berkeley_fission_times_in_seconds/chain%d.txt",f);
    
    readinL(filename);   

    //cout << all_chains[0][0] << endl;
     


    //Now, construct new files
    sprintf(filename2,"chain%d.txt",f);
    ofstream chain2(filename2,ios::out);

    chain2<< all_chains[f][0]<<endl;  //ID
    chain2<< all_chains[f][1] << endl;               //Beam energy?   
    chain2<< all_chains[f][2]<< endl; //Strip x
    chain2<< all_chains[f][3] << endl;                 //Strip y 
    chain2<< all_chains[f][4] << endl;                 //Pixel
    chain2<< all_chains[f][5]<< endl; //Imp. energy
    chain2<< all_chains[f][6]<< endl ;                //Imp. time == 0
    chain2<< all_chains[f][7]<< endl; //First energy
    chain2<< all_chains[f][8]<< endl; //First uncertainty 
    chain2<< all_chains[f][9]<< endl; //First time   
    chain2<< all_chains[f][10]<< endl;
    chain2<< all_chains[f][11]<< endl;
    chain2<< all_chains[f][12]<< endl;
    chain2<< all_chains[f][13]<< endl;
    chain2<< all_chains[f][14]<< endl;
    chain2<< all_chains[f][15]<< endl;
    chain2<< all_chains[f][16]<< endl;
    chain2<< all_chains[f][17]<< endl;
    chain2<< all_chains[f][18]<< endl;
    chain2<< all_chains[f][19]<< endl;
    chain2<< all_chains[f][20]<< endl;
    chain2<< all_chains[f][21]<< endl;
    chain2<< all_chains[f][22]<< endl;
    chain2<< all_chains[f][23]<< endl;
    chain2<<setprecision(6);
    chain2<< all_chains[f][24]/3600.0<< endl;
    
    chain2.close();


  } //Ends loop over chains


  return 0;

} //Ends main function


//Routine to read in chains
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
    else if (m==21) {all_chains[chain_number][m] = temp; m++;}
    else if (m==22) {all_chains[chain_number][m] = temp; m++;}
    else if (m==23) {all_chains[chain_number][m] = temp; m++;}
    else if (m==24) {all_chains[chain_number][m] = temp; m++;}
  }
  chain.close();
}


