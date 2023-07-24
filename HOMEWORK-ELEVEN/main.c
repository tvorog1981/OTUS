#include <termios.h>
#include <fcntl.h>
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
#include<sys/wait.h>








#define BUFLEN 20
#define DO 0xfd
#define WONT 0xfc
#define WILL 0xfb
#define DONT 0xfe
#define CMD 0xff
#define CMD_ECHO 1
#define CMD_WINDOW_SIZE 31
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





void negotiate(int sock, unsigned char *buf, int len) {
    int i;
    if(strlen(buf) > BUFLEN){
      printf("big data \n");
      exit(6);
    } 


      
    if (buf[1] == DO && buf[2] == CMD_WINDOW_SIZE) {
        unsigned char tmp1[10] = {255, 251, 31};
        if (send(sock, tmp1, 3 , 0) < 0){
          printf("error send \n");
	  exit(1);
	}
        unsigned char tmp2[10] = {255, 250, 31, 0, 80, 0, 24, 255, 240};
        if (send(sock, tmp2, 9, 0) < 0){
          printf("error send \n");
	  exit(1);
	}
        return;
    }
     
    for (i = 0; i < len; i++) {
        if (buf[i] == DO)
            buf[i] = WONT;
        else if (buf[i] == WILL)
            buf[i] = DO;
    }
 
    if (send(sock, buf, len , 0) < 0){
      printf("error send \n");
      exit(1);
    }
}
 
static struct termios tin;
 
static void terminal_set(void) {
    // save terminal configuration
    tcgetattr(STDIN_FILENO, &tin);
     
    static struct termios tlocal;
    memcpy(&tlocal, &tin, sizeof(tin));
    cfmakeraw(&tlocal);
    tcsetattr(STDIN_FILENO,TCSANOW,&tlocal);
}
 
static void terminal_reset(void) {
    // restore terminal upon exit
    tcsetattr(STDIN_FILENO,TCSANOW,&tin);
}
 

int main(int argc , char *argv[]) {
    int sock;
    struct sockaddr_in server;
    unsigned char buf[BUFLEN + 1];
    int len;
    int i;
 
    if (argc < 2 || argc > 3) {
        printf("Usage: %s address [port]\n", argv[0]);
        return 1;
    }
    int port = 23;
    // if (argc == 3)
    //  port = atoi(argv[2]);
 
    //Create socket
    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1) {
        perror("Could not create socket. Error");
        return 1;
    }
 
    if(INADDR_NONE != inet_addr(get_dns_to_ip(argv[1]))){
	server.sin_addr.s_addr = inet_addr(get_dns_to_ip(argv[1]));
      }else{
	printf("cannot rezolve %s \n",argv[1]);
        exit(4);

      }
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
 
    //Connect to remote server
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0) {
        perror("connect failed. Error");
        return 1;
    }
    puts("Connected...\n");
 
    // set terminal
    terminal_set();
    atexit(terminal_reset);
     
    struct timeval ts;
    ts.tv_sec = 1; // 1 second
    ts.tv_usec = 0;
 
    while (1) {
        // select setup
        fd_set fds;
        FD_ZERO(&fds);
        if (sock != 0)
            FD_SET(sock, &fds);
        FD_SET(0, &fds);
 
        // wait for data
        int nready = select(sock + 1, &fds, (fd_set *) 0, (fd_set *) 0, &ts);
        if (nready < 0) {
            perror("select. Error");
            return 1;
        }
        else if (nready == 0) {
            ts.tv_sec = 1; // 1 second
            ts.tv_usec = 0;
        }
        else if (sock != 0 && FD_ISSET(sock, &fds)) {
            // start by reading a single byte
            int rv;
            if ((rv = recv(sock , buf , 1 , 0)) < 0){
              printf("Error recv \n");
	      return 1;
	    }else if( strlen(buf) > BUFLEN){
              printf("big data ");
	      exit(7);
	    }
            else if (rv == 0) {
                printf("Connection closed by the remote end\n\r");
                return 0;
            }
 
            if (buf[0] == CMD) {
                // read 2 more bytes
                len = recv(sock , buf + 1 , 2 , 0);
                if (len  < 0){
                  printf("error recv \n");
		  return 1;
		}   
                else if (len == 0) {
                    printf("Connection closed by the remote end\n\r");
                    return 0;
                }
                negotiate(sock, buf, 3);
            }
            else {
	      
                len = 1;
                buf[len] = '\0';
                printf("%s", buf);
                fflush(0);
            }
        }
         
        else if (FD_ISSET(0, &fds)) {
            buf[0] = getc(stdin); //fgets(buf, 1, stdin);
            if (send(sock, buf, 1, 0) < 0){
              printf("Error send \n");
	      return 1;
	    }
            if (buf[0] == '\n') // with the terminal in raw mode we need to force a LF
                putchar('\r');
        }
    }
    close(sock);
    return 0;
}
