 #include<iostream>
#include <stdio.h>
#include <assert.h>
#include <cmath>


using namespace std;


#define tREFI  (3900 * pow(10, -9)) // 3900ns


typedef unsigned            uns;

typedef enum PRIDE_Policy_Enum {
    NO_RFM=0,
    RFM_40=1,
    RFM_16=2, 
} PRIDE_Policy;


/////////////////////////////////////////////////////
// Params
/////////////////////////////////////////////////////


double NUM_TFAW_BANKS            = 22; // we have 64 banks, but only 22 can be concurrently used
uns  OPEN_PAGE_TARDY             =     0;
uns  TARGET_MTTF_YRS  =              10000;
uns  DEFEND_TRANSITIVE_ATTACKS   =     0;
uns  DEFAULT_BUFFER_SIZE         =     (OPEN_PAGE_TARDY)? 6:4;

double WINDOW_ACTS=79; // activations in window

uns   PRIDE_POLICY=NO_RFM; // default


/////////////////////////////////////////////////////
/////////////////////////////////////////////////////

double loss_prob[17]={0,
0.6298	,
0.3048	,
0.1683	,
0.1192	,
0.0952	,
0.0796	,
0.0685	,
0.0601	,
0.0536	,
0.0483	,
0.044	,
0.0404	,
0.0373	,
0.0347	,
0.0324	,
0.0304	};

double loss_prob_rfm40[17]={0,
0.6275	,
0.3046	,
0.1673	,
0.1184	,
0.0945	,
0.0791	,
0.068	,
0.0596	,
0.0531	,
0.0479	,
0.0436	,
0.04	,
0.037	,
0.0344	,
0.0321	,
0.0301  };


double loss_prob_rfm16[17]={0,
0.6202	,
0.3042	,
0.1639	,
0.1159	,
0.0926	,
0.0774	,
0.0664	,
0.0582	,
0.0518	,
0.0466	,
0.0424	,
0.0389	,
0.0359	,
0.0334	,
0.0312	,
0.0292	};


/////////////////////////////////////////////////////
/////////////////////////////////////////////////////

double get_pfail_round(uns th, double ins_prob, double loss_prob){

  double effective_ins_prob = ins_prob * (1- loss_prob);
  double pfail_round =pow(1-effective_ins_prob, th);

  return pfail_round;
}

/////////////////////////////////////////////////////
/////////////////////////////////////////////////////

double get_mttf(uns th, double ins_prob, double loss_prob){
  double time_round = tREFI;

  if(PRIDE_POLICY==RFM_40){
    time_round/=2;
  }

  if(PRIDE_POLICY==RFM_16){
    time_round/=5;
  }

  double pfail_round = get_pfail_round(th, ins_prob, loss_prob);

  double mttf_sec = time_round/pfail_round;

  double mttf_yrs = mttf_sec/(3600*24*365); // sec in year

  return mttf_yrs;
}

/////////////////////////////////////////////////////
// Binary search to find TRH*
/////////////////////////////////////////////////////

uns get_trh_star(double ins_prob, double loss_prob, double target_ttf_yrs){
  double ln_trefi_by_ttf = log( 3.9 / (target_ttf_yrs * 365.0*24*3600*1000000) );
  double trh_star = ln_trefi_by_ttf / log((1-(ins_prob*(1-loss_prob))));
  return trh_star;
}


/////////////////////////////////////////////////////
/////////////////////////////////////////////////////

uns get_tardy(uns buf_size, uns window_size){

  if(OPEN_PAGE_TARDY){
    return (buf_size*window_size-1)/2;
  }else{
    return (buf_size*window_size-1);
  }
}

/////////////////////////////////////////////////////
/////////////////////////////////////////////////////

void print_fig_9(double ins_prob){
   uns trh_star, tardy;

  printf("\n\n***********Printing Data for Fig-9***********\n");
   
  for(uns size=1; size<=16; size++){
     double my_loss_prob = loss_prob[size];
     trh_star = get_trh_star(ins_prob, my_loss_prob, TARGET_MTTF_YRS);

     tardy = get_tardy(size, WINDOW_ACTS); 

     printf("Bufsize: %u\t TRH_STAR(NoTardy): %u\t TRH_STAR(Tardy): %u\n",size, trh_star, trh_star+tardy);
   }

}

/////////////////////////////////////////////////////
/////////////////////////////////////////////////////

void print_table_4(){
   uns trh_star, tardy;
   double my_ins_prob;

   uns size=DEFAULT_BUFFER_SIZE; // default size of buffer

   printf("\n\n***********Printing Table-IV***********\n");

   // PARA-DRFM
   WINDOW_ACTS = 158; 
   my_ins_prob=1.0/160;
   tardy = get_tardy(1, WINDOW_ACTS); 
   trh_star = get_trh_star(my_ins_prob, loss_prob[1], TARGET_MTTF_YRS) + tardy;
   printf("PARA-DRFM        \tTRH_STAR: %u\t \n", trh_star);

   // PARA-DRFM+
   WINDOW_ACTS=79;
   my_ins_prob=1.0/80 ;
   tardy = get_tardy(1, WINDOW_ACTS); 
   trh_star = get_trh_star(my_ins_prob, loss_prob[1], TARGET_MTTF_YRS) + tardy;
   printf("PARA-DRFM+        \tTRH_STAR: %u\t \n", trh_star);

   // PRIDE
   WINDOW_ACTS=79;
   my_ins_prob=1/80.0;
   tardy = get_tardy(size, WINDOW_ACTS); 
   trh_star = get_trh_star(my_ins_prob, loss_prob[size], TARGET_MTTF_YRS) + tardy;
   printf("PRIDE             \tTRH_STAR: %u\t \n", trh_star);

   printf("\n\n");

   // return params to default
   PRIDE_POLICY=NO_RFM;
   WINDOW_ACTS=79;

}

/////////////////////////////////////////////////////
/////////////////////////////////////////////////////

void print_table_5(){
   uns trh_star, tardy;
   double my_ins_prob;

   uns size=DEFAULT_BUFFER_SIZE; // default size of buffer

   printf("\n\n***********Printing Table-V***********\n");

   // PRIDE (1 mit per 2 tREFI)
   PRIDE_POLICY=NO_RFM;
   my_ins_prob=1/159.0;
   WINDOW_ACTS=158;
   tardy = get_tardy(size, WINDOW_ACTS); 
   trh_star = get_trh_star(my_ins_prob, loss_prob[size], TARGET_MTTF_YRS/2) + tardy;
   printf("PRIDE (0.5x)        \tTRH_STAR-S: %u\n", trh_star);

   // PRIDE
   PRIDE_POLICY=NO_RFM;
   my_ins_prob=1/80.0;
   WINDOW_ACTS=79;
   tardy = get_tardy(size, WINDOW_ACTS); 
   trh_star = get_trh_star(my_ins_prob, loss_prob[size], TARGET_MTTF_YRS) + tardy;
   printf("PRIDE        \tTRH_STAR-S: %u\n", trh_star);

   // PRIDE+RFM40
   PRIDE_POLICY=RFM_40;
   WINDOW_ACTS=40;
   tardy = get_tardy(size, WINDOW_ACTS); 
   my_ins_prob=1/41.0;
   trh_star = get_trh_star(my_ins_prob, loss_prob_rfm40[size], TARGET_MTTF_YRS*2)+tardy;
   printf("PRIDE+RFM40  \tTRH_STAR-S: %u\n", trh_star);

   // PRIDE+RFM16
   PRIDE_POLICY=RFM_16;
   WINDOW_ACTS=16;
   tardy = get_tardy(size, WINDOW_ACTS); 
   my_ins_prob=1/17.0;
   trh_star = get_trh_star(my_ins_prob, loss_prob_rfm16[size], TARGET_MTTF_YRS*5)+tardy;
   printf("PRIDE+RFM16  \tTRH_STAR-S: %u\n", trh_star);

   printf("\n\n");

   // return params to default
   PRIDE_POLICY=NO_RFM;
   WINDOW_ACTS=79;

}

/////////////////////////////////////////////////////
/////////////////////////////////////////////////////

void print_table_6(){
   uns trh_star, tardy;
   double my_ins_prob;

   uns size=DEFAULT_BUFFER_SIZE; // default size of buffer

   printf("\n\n***********Printing Table-VI***********\n");

   // PRIDE
   my_ins_prob=1/80.0;
   WINDOW_ACTS=79;
   tardy = get_tardy(size, WINDOW_ACTS); 
   trh_star = get_trh_star(my_ins_prob, loss_prob[size], TARGET_MTTF_YRS) + tardy;
   printf("PRIDE        \tTRH_STAR-S: %u\t TRH_STAR-D: %u\n", trh_star, trh_star/2);

   // PRIDE+RFM40
   PRIDE_POLICY=RFM_40;
   WINDOW_ACTS=40;
   tardy = get_tardy(size, WINDOW_ACTS); 
   my_ins_prob=1/41.0;
   trh_star = get_trh_star(my_ins_prob, loss_prob_rfm40[size], TARGET_MTTF_YRS*2)+tardy;
   printf("PRIDE+RFM40  \tTRH_STAR-S: %u\t TRH_STAR-D: %u\n", trh_star, trh_star/2);

   // PRIDE+RFM16
   PRIDE_POLICY=RFM_16;
   WINDOW_ACTS=16;
   tardy = get_tardy(size, WINDOW_ACTS); 
   my_ins_prob=1/17.0;
   trh_star = get_trh_star(my_ins_prob, loss_prob_rfm16[size], TARGET_MTTF_YRS*5)+tardy;
   printf("PRIDE+RFM16  \tTRH_STAR-S: %u \t TRH_STAR-D: %u\n", trh_star, trh_star/2);

   printf("\n\n");

   // return params to default
   PRIDE_POLICY=NO_RFM;
   WINDOW_ACTS=79;
}

/////////////////////////////////////////////////////
/////////////////////////////////////////////////////

void print_table_8(){
   uns trh_star, tardy;
   double my_loss_prob, my_ins_prob;

   uns size=DEFAULT_BUFFER_SIZE; // default size of buffer
   my_loss_prob = loss_prob[size];

   WINDOW_ACTS=79;
   my_ins_prob=1/80.0;
   tardy = get_tardy(size, WINDOW_ACTS); 

   printf("\n\n***********Printing Table-VIII***********\n");

   for(uns ii=100; ii<=1000000; ii *= 10){
     TARGET_MTTF_YRS  =  ii;
     trh_star = get_trh_star(my_ins_prob, my_loss_prob, ii)+tardy;
     printf("%u Years\t%4.2f Years\t TRH_STAR-S: %u\t TRH_STAR-D: %u\n", ii, (double)(ii)/NUM_TFAW_BANKS, trh_star, trh_star/2);
   }

   // return params to default
   TARGET_MTTF_YRS  =  10000;

   printf("\n\n");
}

/////////////////////////////////////////////////////
/////////////////////////////////////////////////////

void PrintMTTF( double TTF_system_years )
{
    double TTF_system_sec = TTF_system_years * (365*24*60*60);

    double TTF_system_min = TTF_system_sec / 60;
    double TTF_system_hrs = TTF_system_sec / (60*60);
    double TTF_system_days = TTF_system_sec / (24*60*60);

    std::string metric = "";
    double val;
    
    int print = 1;
    if( (val=TTF_system_sec) < 1 )
    {
        print = 0;
        cout<<"<1 sec";
    }
    else if( (val=TTF_system_sec) < 60 )
    {
        metric = "sec";
    }
    else if ( (val=TTF_system_min) < 60 )
    {
        metric = "min";
    }
    else if ( (val=TTF_system_hrs) < 24 )
    {
        metric = "hrs";
    }
    else if ( (val=TTF_system_days) < 365 )
    {
        metric = "days";
    }
    else if ( (val=TTF_system_years) < 1000000 )
    {
        metric = "years";
    }
    else 
    {
        print = 0;
        // val /= 1000000;
        // metric = "mil_years";
        cout<<">1 mil_years";

    }
    
//     printf("%5.2E yrs", TTF_system_years);
    if (print ) cout<<int(val+1)<<" "<<metric;
}


void print_table_9(){
  double my_loss_prob, my_ins_prob, my_bank_mttf, my_sys_mttf;
  uns trhd;
  uns tardy;

  uns size=DEFAULT_BUFFER_SIZE; // default size of buffer
  
  printf("\n\n***********Printing Table-IX***********\n");

  for(trhd=4800; trhd >= 200; trhd -= 200){
    printf("TRDH-D: %u\t", trhd);
    
    // PRIDE
    PRIDE_POLICY=NO_RFM;
    WINDOW_ACTS=79;
    tardy = get_tardy(size, WINDOW_ACTS); 
    
    my_ins_prob=1/80.0;
    my_bank_mttf = get_mttf(trhd*2-tardy, my_ins_prob, loss_prob[size]);
    my_sys_mttf  = my_bank_mttf/NUM_TFAW_BANKS;

    PrintMTTF( my_sys_mttf );
    
    // PRIDE+RFM40
    PRIDE_POLICY=RFM_40;
    WINDOW_ACTS=40;
    tardy = get_tardy(size, WINDOW_ACTS); 

    my_ins_prob=1/41.0;
    my_bank_mttf = get_mttf(trhd*2-tardy, my_ins_prob, loss_prob_rfm40[size]);
    my_sys_mttf  = my_bank_mttf/NUM_TFAW_BANKS;

    printf("\t");
    PrintMTTF( my_sys_mttf );
  
    // PRIDE+RFM16
    PRIDE_POLICY=RFM_16;
    WINDOW_ACTS=16;
    tardy = get_tardy(size, WINDOW_ACTS); 

    my_ins_prob=1/17.0;
    my_bank_mttf = get_mttf(trhd*2-tardy, my_ins_prob, loss_prob_rfm16[size]);
    my_sys_mttf  = my_bank_mttf/NUM_TFAW_BANKS;

    printf("\t");
    PrintMTTF( my_sys_mttf );

    printf("\n");

    if(trhd==4800){trhd=2200;} // skip after first row in table
  }
  
  printf("\n\n");
  
  // return params to default
  PRIDE_POLICY=NO_RFM;
  WINDOW_ACTS=79;
}

/////////////////////////////////////////////////////
/////////////////////////////////////////////////////

int main(int argc, char* argv[]){

   double ins_prob=(double)(1)/(double)(WINDOW_ACTS);

   if(DEFEND_TRANSITIVE_ATTACKS){
     ins_prob=(double)(1)/(double)(WINDOW_ACTS+1);
   }

   print_fig_9(ins_prob);

   print_table_4();

   print_table_5();

   print_table_6();

   print_table_8();

   print_table_9();

  return 0;
}



