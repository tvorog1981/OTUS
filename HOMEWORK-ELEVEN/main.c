#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>



int main(int argc , char ** argv){



	// create a socket
	int network_socket;
	network_socket = socket(AF_INET, SOCK_STREAM, 0);
	
	// specify an address for the socket
	struct sockaddr_in server_address;
	 server_address.sin_family = AF_INET;

	server_address.sin_port = htons(80);
	char * host_connect = "https://google.com";
	server_address.sin_addr.s_addr = host_connect;

	int connection_status = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));
	// check for error with the connection
	if (connection_status == -1){
		printf("There was an error making a connection to the remote socket \n\n");
	}
	
	// receive data from the server
	char server_response[256];
	recv(network_socket, &server_response, sizeof(server_response), 0);

	// print out the server's response
	printf("The server sent the data: %s\n", server_response);

	// and then close the socket
	close(network_socket);

       



  return EXIT_SUCCESS;
}
