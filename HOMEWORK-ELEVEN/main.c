#include<unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>          
#include <netdb.h>        
#include <arpa/inet.h>      
#include <netinet/in.h>
#include<string.h>
char * get_dns_to_ip(char * hostname){
  struct hostent *host;
  struct in_addr h_addr;
  if (( host = gethostbyname(hostname)) == NULL){
        fprintf(stderr, "USAGE: nslookup <inet_address>\n");
        exit(1);
  }

 h_addr.s_addr = *((unsigned long *) host-> h_addr_list[0]);
 // fprintf(stdout, "%s\n", inet_ntoa(h_addr));

 return inet_ntoa(h_addr);

}

int main(int argc , char ** argv){

  if(argc < 2 || argc > 3){
    printf("You want %s <domain> \n",argv[0]);
    exit(11);
  }

  // printf("ip address -> %s \n", get_dns_to_ip(argv[1])); 
 ;
        int client_socket;
	client_socket = socket(AF_INET, SOCK_STREAM, 0);	
	if(client_socket < 0){
	  perror("socket");
	  exit(12);
	}
	// specify an address for the socket
         ;
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(23);
	server_address.sin_addr.s_addr = inet_addr(get_dns_to_ip(argv[1]));
        while( 0 !=  connect(client_socket, (struct sockaddr *) &server_address, sizeof(server_address))){
	  sleep(1);
	}
       
	for(;;){
	  char s_q[256];
         char response[1024];
	 char * s;
         bzero(response,1024);
	 bzero(s_q,256);
	 read(client_socket, &response, sizeof(response));
	 fflush(stdout);
	 for(int i = 0 ; i < strlen(response);i++){
           //if(){
	     // s = fgets(s_q,256,stdin);
	     
	     // }
	   printf("%c\n",response[i]);
	   
	 }
	 // printf("The server sent the data: %s\n", response);
        
          

	}
	close(client_socket);
	return EXIT_SUCCESS;
}
