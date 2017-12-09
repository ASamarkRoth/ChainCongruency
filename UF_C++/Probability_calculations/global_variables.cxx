const int allowed_max_chain_length = 8; //All arrays are this long (max_chain_length in main defines how many steps to consider)
const int allowed_nr_of_chains = 9700000; //It is not possible to have more chains than this

int ref_nr_in_step[allowed_max_chain_length] = {0};	
int nr_in_step[allowed_max_chain_length] = {0};
int n_fom[allowed_max_chain_length] = {0};

//Must-haves
int chain_number;
int nr_of_chains_in_set = 0;
int nr_of_sets_of_random_chains;
int scenario = 0;
int no_of_decays = 0;
int chain_to_evaluate = 0;


double time_fom[allowed_max_chain_length] = {0.0};
double ref_halflife[allowed_max_chain_length] = {0.0};

vector<int> chains_to_consider (allowed_nr_of_chains,0); //The array will be reduced later, if necessary
vector< vector< double> > all_chains;  //The size is defined later

bool external_reference = false;

//Half-lives
double halflife_ref[allowed_max_chain_length] = {0.0};
double halflife_ref_low[allowed_max_chain_length] = {0.0};
double halflife_ref_high[allowed_max_chain_length] = {0.0};

//Figure-of-Merit
double s[allowed_max_chain_length] = {0.0};
double s_high[allowed_max_chain_length] = {0.0};
double s_low[allowed_max_chain_length] = {0.0};
double s_up[allowed_max_chain_length] = {0.0};
double s_down[allowed_max_chain_length] = {0.0};

double s1_1;
double s1_2;
double s2_1;
double s2_2;
double s3_1;
double s3_2;
double mean123;
double mean23;
double mean13;
double mean12;
double s_sum[allowed_max_chain_length] = {0.0};

string filename = "";
string path = "";

int nr_random_chains_counter = 0;
double FoM_smeared[allowed_max_chain_length] = {0.0};
double FoM_smeared_average = 0;
double FoM_mean_sim_smeared = 0.0;


//Stuff to be implemented later
//int nr_of_logbins = 2600;
//double log_start = -6.0;
//double log_step = 0.0045;

const int nr_of_logbins = 80;
double log_start = -6.5;
double log_step = 0.1;

double log_lowlim = exp(log_start);
double log_hilim = exp(log_start+(nr_of_logbins+1)*log_step);

double tottot = 0.0;
double tottot1 = 0.0;
double tottot2 = 0.0;
double tottot3 = 0.0;

//Spectra
TH1F* h_implant_energy;
TH1F* h_FoM_smeared_MC;
TH1F* h_Schmidt[allowed_max_chain_length];
TH1F* h_Schmidt_gen;

TH1F* h_decay_energy[allowed_max_chain_length];
TH1F* h_decay_time[allowed_max_chain_length];
TH1F* h_decay_time_ln[allowed_max_chain_length];
TH1F* h_decay_time_logbins[allowed_max_chain_length];
TH1F* h_FoM_smeared_avg[allowed_max_chain_length];

TF1* picpic1;
TF1* picpic2;
TF1* picpic3;
