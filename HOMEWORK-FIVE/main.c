#include<stdio.h>
#include<stdlib.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <inttypes.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/un.h>
#include <fcntl.h>         
#include <limits.h>       
#include <sys/stat.h>
#include <sys/wait.h>
#include<stdbool.h>
#include <sys/uio.h>
#define BUFF_SOCK 255

void  read_from_buff(char *fd_buf, int size,int * code, int  * size_file){
  FILE * fd = NULL;
  int ff = fork();

   if(ff == 0){
     int fff = fork();
     if( fff == 0){
  fd_buf[strcspn(fd_buf, "\n")] = 0;
 struct stat file;
 // fprintf(stdout,"[%s]",fd_buf);
    fd = fopen(fd_buf, "r");
  if(fd != NULL){
    //    printf("file 111  exist %s\n",fd_buf);
     *code = 1;
     stat(fd_buf, &file);
     *size_file = file.st_size;
     //printf("size -> %ld",*size_file);
  }else{

    *code = 2;
  }
     }

     wait(NULL);

     }
 if(ff > 0 ){
 wait(NULL);

 // printf("code %d",code);
   fclose(fd);
   }

  }




int main(){


  char *  path_sock = "/tmp/sock_bind";
  int server_sock;
  int client_sock;
 int status;
  int code = 0;
  int size_file;
  char buff_sock[BUFF_SOCK];
  server_sock = socket(AF_UNIX,SOCK_STREAM,0);

  if(server_sock <  0  ){
    printf("socket faild\n"); 
    exit(1);}


  struct sockaddr_un saddr;

  memset((void *)&saddr,0,sizeof(saddr));

  saddr.sun_family = AF_UNIX;

  strcpy(saddr.sun_path, path_sock);

  if(bind(server_sock,(struct sockaddr*)&saddr,sizeof(saddr)) < 0 ){
      printf("bind faild\n"); 
    exit(2);
  }
  
  
  memset(&buff_sock, 0 ,sizeof(buff_sock)); 
  FILE * config = NULL;
  listen(server_sock,10);
  printf("Ready to data from client \n");

  fflush(stdin);
  
  while(true){

    int f = fork();

 if(f == 0){  
   if(config !=NULL){
     fclose(config);
     config = NULL;
   } 
   char ch ;
   int flag = 1;
   int rez ;
   char count[10];
   int file_count;
   memset(count,0, 10);
   config = fopen("config.file","r");
   if(config == NULL){
     printf("config file not exist\n");
     exit(11);
   }else{
     int i = 0;
     while((ch = getc(config)) != EOF){
       if(ch == '='){
	 flag = 0;
	 continue;
       }               
       if(flag == 0){
	 // printf("%c",ch);
	 count[i] = ch;
       i++;
       }
   }
   }
      file_count = strtoumax(count, NULL, 10);
   //   printf("count %s " ,count);  
      //      printf("real size count %d size config %d " , file_count,file_count);

   
   
   client_sock = accept(server_sock , NULL, NULL);
     recv(client_sock,&buff_sock,BUFF_SOCK,0);

     read_from_buff(buff_sock,strlen(buff_sock),&code,&size_file);
    
 if (code == 1){
       memset(buff_sock,0,BUFF_SOCK);
       if(size_file != file_count){
       sprintf(buff_sock,"real size file %d size in config %d\n",size_file,file_count);
       }else{
      sprintf(buff_sock,"real size file %d \n",size_file);
       }
       send(client_sock,&buff_sock,BUFF_SOCK,0);
                 shutdown(client_sock,0);    
	       shutdown(client_sock,1);	       
	       fclose(config);

	       config = NULL;
 }

 else if(code == 2){
   int ffff = fork();

   if(ffff == 0){
   memset(buff_sock,0,BUFF_SOCK);
       sprintf(buff_sock,"file not exist \n");
         send(client_sock,&buff_sock,BUFF_SOCK,MSG_CONFIRM );
	       shutdown(client_sock,0);    
	       shutdown(client_sock,1);
                       
     }   
 }

 wait(NULL);
 if(config !=NULL){
  
   //  unlink((const char )config);
 }
 

   
 //       fclose(config);
 
 }else{
   sleep(5);
 }


  waitpid(-1,&status,0);
  // send(client_sock,&buff_sock,BUFF_SOCK,0);


 
     
  }

     close(server_sock);
     

 

  
  return EXIT_SUCCESS;
}
