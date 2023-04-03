#include"parsing.h"


int main(){

  init_log();

  char * w = "text warning";
  char * d = "text debug";
  char * i = "text info";
  char * e = "text error";
  w_log(w);
  d_log(d);
  i_log(i);
  e_log(e);
  
  




  destroy_log();



  return EXIT_SUCCESS;
}
