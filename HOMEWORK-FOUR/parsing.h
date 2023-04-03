#ifndef _PARSING_LOG_FILE_
#define  _PARSING_LOG_FILE_
#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>
#include<string.h>
#include"parsing.h"
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<time.h>
#include<execinfo.h>
FILE * fd;
#define FILE_NAME  "file.log"
#define w_log(str) warning_log("%s",(str))
#define i_log(str) info_log("%s",(str))
#define d_log(str) debug_log("%s",(str))
#define e_log(str) error_log("%s",(str))


void init_log();
void destroy_log();
void debug_log(char * format, ...);
void info_log(char * format , ...);
void warning_log(char * format, ...);
void error_log(char * format,...);
#endif
