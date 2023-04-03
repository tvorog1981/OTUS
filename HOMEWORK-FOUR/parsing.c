
#include"parsing.h"

/* init log */
void init_log(){
  /* protected file from read and change  */
  fd = fopen(FILE_NAME,"w");

  if(fd < 0 ){
    fprintf(stderr,"dont create file log \n");
    exit(1);
  }
  
} 



/* destroy log */
void destroy_log(){

  if( fclose(fd) < 0){
 fprintf(stderr,"dont close file log \n");
    exit(1);
  }
}


/* debug */
void debug_log(char * format, ...){
  va_list ap;
  time_t t = time(NULL);
  struct tm* now_time = localtime(&t);
  char * debug = "debug";
  va_start(ap,format);
  if(!strcmp(format,"%s")){
    char * p = va_arg(ap,char*);
    fprintf(fd," [Date %04d:%02d:%02d  %02d:%02d:%02d] [%s]-> on line [ %d ] in file [%s] -> text %s \n"
	    ,now_time->tm_year +1900,
	    now_time->tm_mon+1,
	    now_time->tm_mday,
	    now_time->tm_hour,
	    now_time->tm_min,
	    now_time->tm_sec,
	    debug,__LINE__,__FILE__,p);

  }
  
    va_end(ap);


  
}



/* info */
void info_log(char * format , ...){
  va_list ap;
  time_t t = time(NULL);
  struct tm* now_time = localtime(&t);
  char * info = "info";
  va_start(ap,format);
  if(!strcmp(format,"%s")){
    char * p = va_arg(ap,char*);
    fprintf(fd," [Date %04d:%02d:%02d  %02d:%02d:%02d] [%s]-> on line [ %d ] in file [%s] -> text %s \n"
	    ,now_time->tm_year +1900,
	    now_time->tm_mon+1,
	    now_time->tm_mday,
	    now_time->tm_hour,
	    now_time->tm_min,
	    now_time->tm_sec,
	    info,__LINE__,__FILE__,p);

  }
  
    va_end(ap);



}
/* warning */
void warning_log(char * format, ...){
  va_list ap;
  time_t t = time(NULL);
  struct tm* now_time = localtime(&t);
  char * warning = "warning";
  va_start(ap,format);
  if(!strcmp(format,"%s")){
    char * p = va_arg(ap,char*);
    fprintf(fd," [Date %04d:%02d:%02d  %02d:%02d:%02d] [%s]-> on line [ %d ] in file [%s] -> text %s \n"
	    ,now_time->tm_year +1900,
	    now_time->tm_mon+1,
	    now_time->tm_mday,
	    now_time->tm_hour,
	    now_time->tm_min,
	    now_time->tm_sec,
	    warning,__LINE__,__FILE__,p);

  }
  
    va_end(ap);

   
}



/* error */
void error_log(char * format,...){
     va_list ap;
  time_t t = time(NULL);
  struct tm* now_time = localtime(&t);
  char * error = "error";
  va_start(ap,format);
  if(!strcmp(format,"%s")){
    char * p = va_arg(ap,char*);
    fprintf(fd," [Date %04d:%02d:%02d  %02d:%02d:%02d] [%s]-> on line [ %d ] in file [%s] -> text %s \n"
	    ,now_time->tm_year +1900,
	    now_time->tm_mon+1,
	    now_time->tm_mday,
	    now_time->tm_hour,
	    now_time->tm_min,
	    now_time->tm_sec,
	    error,__LINE__,__FILE__,p);

  }
int BT_BUF_SIZE = 100;

 int nptrs;
           void *buffer[BT_BUF_SIZE];
           char **strings;
	   /* stack run */
           nptrs = backtrace(buffer, BT_BUF_SIZE);
           printf("backtrace() returned %d addresses\n", nptrs);

	   // backtrace_symbols_fd(buffer, nptrs, STDOUT_FILENO);
          

           strings = backtrace_symbols(buffer, nptrs);
           if (strings == NULL) {
               perror("backtrace_symbols");
               exit(EXIT_FAILURE);
           }

           for (int j = 0; j < nptrs; j++)
               printf("%s\n", strings[j]);

           free(strings);
  
    va_end(ap);

}















