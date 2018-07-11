#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>  // structures for networking

int main(){
	char server_message[256] = "You have reached server\n";
	int server_socket;
	server_socket = socket(AF_INET, SOCK_STREAM, 0); // 0 default TCP

	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);
	server_address.sin_addr.s_addr = INADDR_ANY;

	bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));

	listen(server_socket,5);
	
	int client_socket;
	while(1) {
		client_socket = accept(server_socket,NULL,NULL);
		send(client_socket, server_message, sizeof(server_message),0);
		close(client_socket);
	}
	close(server_socket);
	return 0;
}
