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
#define BUFF_SIZE 1024


int read_file_config();
void Deamon(int);
int socket_create(void);





int main(int argc ,char ** argv){
   char start;
   
  if(argc < 2 || argc > 2){
    printf("params  -> -d n");
    printf("You want to %s <params>\n",argv[0]);
    exit(12);

  }else{
    if( strcmp(argv[1], "-d") == 0){
      start = 'd';
    }else{
      printf("parameters %s\n",argv[1]);
      printf("params  -> -d \n");
      printf("You want to %s <params>\n",argv[0]);
      exit(13);

    }
  }

  int server_sock = socket_create();
  //int r =  read_file_config();
  if('d' == start){
    printf("Deamon started\n");
    Deamon(server_sock);
  }


  return EXIT_SUCCESS;
}


void Deamon(int server_sock){
  pid_t pid;
  int rez;
  int client_sock;
   void sig_child(int);
  char buff_sock[BUFF_SOCK];
  bzero(buff_sock,BUFF_SOCK);
  listen(server_sock,10);

  for(;;){
    signal(SIGCHLD,sig_child);
      client_sock = accept(server_sock,NULL,NULL);
      if(client_sock > 0 ){
	pid = fork();
	if(pid == 0){
            rez =  read_file_config();

	  if(rez == -1){
	    const char * r = "Can't read config file\n";
             send(client_sock,r,strlen(r),0);     
	  }
	   if(rez == -2){
	    const char * r = "Can't read size file\n";
             send(client_sock,r,strlen(r),0);     
	  }
	   if(rez > 0){
	     char b[255];
	     sprintf(b,"Size of file %d\n",rez);
                send(client_sock,b,strlen(b),0);     
	   }
	}
  

      }
      wait(NULL);     
      
      

      shutdown(client_sock,0);    
      shutdown(client_sock,1);	
    

  }
}


int read_file_config(){
  int flag = 1;
  char ch;
  char buff[BUFF_SIZE];
  bzero(buff,sizeof(buff));
  FILE * fd = fopen("config.file", "r");
  if(fd == NULL ){
    printf("Can't open config file \n");
    return -1;
    }
  int j = 0;
  while((fread(&ch,sizeof(ch),1,fd)) != 0){
 
    if(ch != '=' && flag == 1){
      continue;   
    }
    if(ch == '='){
      flag = 0 ;
      continue;
    }
    if(flag == 0 && ch != '\n'){   
      buff[j++] =ch;
    }

  }
  //for(int i = 0 ; i < strlen(buff);i++){
  //  printf("\n -> buff[%d] ->%c",i,buff[i]);
  // }

  int  fd_size = open(buff,O_RDONLY);

  struct stat st;
  if(fd_size < 0 ){
    printf("Can't read size of file \n");
    return -2;
  }else{
    fstat(fd_size,&st);
    //   printf("size -> %d", st.st_size);

  }
  
  
  close(fd_size);
  fclose(fd);
  return st.st_size;
}





int socket_create(void){
  char *  path_sock = "/tmp/sock_bind";
  int server_sock;
  server_sock = socket(AF_UNIX,SOCK_STREAM,0);

  if( server_sock <  0  ){
    printf("socket faild\n"); 
    exit(1);
  }


  struct sockaddr_un saddr;

  memset((void *)&saddr,0,sizeof(saddr));
  saddr.sun_family = AF_UNIX;
  strcpy(saddr.sun_path, path_sock);

  if(bind(server_sock,(struct sockaddr*)&saddr,sizeof(saddr)) < 0 ){
      printf("bind faild\n"); 
     exit(2);
  }
  

  return server_sock;
}

 void sig_child(int sig)
        {
         pid_t pid;
         int stat;
         while ((pid=waitpid(-1,&stat,WNOHANG))>0)
         {
          }
          return;
        }
