#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<stdbool.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
#define PORT 8001
#define BACKLOG 10
#define SIZE_HEADER  8000
char HEADER[SIZE_HEADER];

void print_err(char * str,int code){
  printf("Error %s \n",str);
  exit(code);
}

typedef enum{
  ERROR_SOCK = -1,
  ERROR_BIND = -2,
  ERROR_LISTEN = -3,
  ERROR_SERVER = -4,
  ERROR_CLIENT = -5
}t_errors;

void report(struct sockaddr_in * serverAddress );
int create_sock();
void setHttpHeader(char * header,char *page);


void parse_page(char * page){
  char GET[4]={0};
  char PAGE[100] = {0};
  int flag_get = 1;
  int flag_page = 1;
  int j = 0;
  for(int i = 0 ; page[i] != '\n';i++){
    if(page[i] != ' ' && flag_get == 1){
      GET[i] = page[i];
      }else if(page[i] == ' ' && flag_get == 1){
      flag_get = 0;
      flag_page =0;
    }else if( flag_page == 0 && page[i] != ' '){
      PAGE[j++] = page[i];
    }else if(page[i] == ' ' ){
      flag_page = 3;
    }
       
    
      }
  //  printf("\n GET => %s\n",GET);
  // printf("\n PAGE => %s\n",PAGE);
  if(strcmp("/", PAGE) == 0){
          printf("\nmain\n");
	  setHttpHeader(HEADER, "index.html");
  } 
 else if(strcmp("/about", PAGE) == 0){
    printf("\nabout\n");
    setHttpHeader(HEADER, "about.html");
   
 }else if (strcmp("/articles", PAGE) == 0){
        printf("\narticles\n");
	setHttpHeader(HEADER, "articles.html");
  }else{
    printf("\npage 404\n");
    setHttpHeader(HEADER, "page404.html");

  }
}

void add_header(char * header){
    bzero(header,SIZE_HEADER);
    char * h = "HTTP/1.1 200 OK\r\n\n";
    for(int i = 0 ;'\0' !=  h[i];i++){
      header[i] = h[i];
    }
}




int main(int argc , char ** argv){
  //  printf("%s",HEADER);
  int sock = create_sock();
  //  setHttpHeader(HEADER,"index.html");

  int client_sock;

  char buff[1000]= {0};
  add_header(HEADER);
    printf("%s",HEADER);
  while(true){
       client_sock = accept(sock, NULL,NULL);

       //const int flags = fcntl(client_sock, F_GETFL, 0);
  //fcntl(client_sock, F_SETFL, flags | O_NONBLOCK);
       //  send(client_sock, HEADER, sizeof(HEADER), 0);
  recv(client_sock,buff, 10000,0);
  parse_page(buff);
  printf("%s",buff);
  printf("%s",HEADER);
  send(client_sock, HEADER, sizeof(HEADER), 0);
  add_header(HEADER);
  
 close(client_sock);

  }

  return EXIT_SUCCESS;
}  













  int create_sock(){

int sock = socket(  AF_INET, SOCK_STREAM,  0 );

//  const int flags = fcntl(sock, F_GETFL, 0);
// fcntl(sock, F_SETFL, flags | O_NONBLOCK);
  
 struct sockaddr_in serverAddress;
  bzero(&serverAddress,sizeof(serverAddress));

  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(PORT);
  serverAddress.sin_addr.s_addr = INADDR_ANY;


  int bind_rez = bind( sock, (struct sockaddr *)&serverAddress, sizeof(serverAddress));

  if(bind_rez < 0){
    print_err("bind",ERROR_BIND);

  }
  int listen_rez  = listen(sock,BACKLOG);

  if(listen_rez < 0 ){
    print_err("listen",ERROR_LISTEN);
   
  }
			   
  report(&serverAddress);



  

  return sock;

}





void setHttpHeader(char * header, char * page){

  FILE *html = fopen(page,"r");
  if(html == NULL){
    printf("Can't open html file \n");
    exit(-5);
  }
  char line[100];
  bzero(line,sizeof(line));
  char response[8000];
  bzero(response,sizeof(response));

  while(fgets(line,100, html) != 0){

    strcat(response,line);

  }
  strcat(header,response);

}



void report(struct sockaddr_in * serverAddress){
  char host[INET6_ADDRSTRLEN];
  char server[NI_MAXSERV];

  socklen_t len = sizeof(*serverAddress);
  int err = getnameinfo( (struct sockaddr*)serverAddress, len, host ,sizeof(host),server, sizeof(server), NI_NUMERICHOST);
  if(err < 0){
    print_err("error server",ERROR_SERVER);
  }
    printf("\n\n\tServer listening on http://%s:%s\n", host, server);
}
