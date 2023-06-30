#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<sys/epoll.h>
#include<netinet/in.h>
#include<fcntl.h>
#include<sys/socket.h>
#include<stdbool.h>
#include<string.h>
#define MAX_EVENTS 10
#define MAX_BUFF 1024


#define errors_handler(msg) \
  do{perror(msg); exit(EXIT_FAILURE);}while(0)


char *reply =
"HTTP/1.1 200 OK\n"
"Date: Thu, 30 JUN 2023 12:27:04 GMT\n"
"Server: Apache/2.2.3\n"
"Last-Modified: Wed, 30  Jun 2023 16:05:58 GMT\n"
"ETag: \"56d-9989200-1132c580\"\n"
"Content-Type: text/html\n"
"Content-Length: 15\n"
"Accept-Ranges: bytes\n"
"Connection: close\n"
"\n"
"sdfkjsdnbfkjbsf";

int setnonblock(int fd){
  int flag;
  if(-1 == (flag =fcntl(fd,F_GETFL,0))){
    flag = 0;
  }
  return fcntl(fd,F_SETFL,flag |O_NONBLOCK);
}

void run(){
  struct epoll_event ev;
  struct epoll_event  events[MAX_EVENTS];

  struct sockaddr_in server_address;
  struct sockaddr_in client_address;
  char buff[MAX_BUFF];

  int listen_sock;
  int connect_sock;
  int nfds;
  int epoll_fd;
  int n = 0;
  
  listen_sock = socket(AF_INET,SOCK_STREAM,0); 

  if(0 > listen_sock){
    errors_handler("socket");
  }

   memset(&client_address,0,sizeof(struct sockaddr_in));
   memset(&server_address,0,sizeof(struct sockaddr_in));

   server_address.sin_family = AF_INET;
   server_address.sin_port = htons(8001);
   server_address.sin_addr.s_addr = INADDR_ANY;

   if(0 > bind(listen_sock,(struct sockaddr*)&server_address,sizeof(server_address))){
         errors_handler("bind");
       }
   if ( 0 > listen(listen_sock,20)){
       errors_handler("listen");
     }

   if( 0 >  (epoll_fd  = epoll_create(10))){
       errors_handler("create_epoll");
     }
  
   ev.events = EPOLLIN;
   ev.data.fd = listen_sock;
   if( 0 > epoll_ctl(epoll_fd, EPOLL_CTL_ADD,listen_sock,&ev)){
     errors_handler("epoll_ctl: listen_sock");
   }

   printf("Server started\n");
   while(true){   
   if(0 > (nfds = epoll_wait(epoll_fd,events,MAX_EVENTS,-1))){
     errors_handler("epoll wait");
   }
     printf("event => %d\n",nfds);
   }
   
   
}

int main(){
  signal(SIGPIPE,SIG_IGN);
  run();   




  
  return EXIT_SUCCESS;
}
