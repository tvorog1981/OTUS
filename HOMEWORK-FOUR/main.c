#include"parsing.h"
int main(){

  init_log();

  char * w = "text warning";
  char * d = "text debug";
  char * i = "text info";
  char * e = "text error";
  warning_log("%s",w);
  debug_log("%s",d);
  info_log("%s",i);
  error_log("%s",e);
  
  




  destroy_log();



  return EXIT_SUCCESS;
}
