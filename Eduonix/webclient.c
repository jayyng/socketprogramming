// How to debug:
// www.thegeekstuff.com/2010/03/debug-c-program-using-gdb
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>  // structures for networking
#include <arpa/inet.h> // for address conversions

int main(int argc, char *argv[]){
	char *address;
	address = argv[1];
	printf("address: %s\n", address);
	int client_socket;
	client_socket = socket(AF_INET, SOCK_STREAM, 0); // 0 default TCP

	struct sockaddr_in remote_address;
	remote_address.sin_family = AF_INET;
	remote_address.sin_port = htons(80);
	inet_aton(address, &remote_address.sin_addr.s_addr);

	connect(client_socket, (struct sockaddr *)&remote_address, sizeof(remote_address));

	char request[] = "GET / HTTP/1.1\r\n\r\n";
	char response[4096];

	send(client_socket, request, sizeof(request), 0);
	recv(client_socket, &response, sizeof(response), 0);

	printf("response: %s\n", response);
	close(client_socket);

	return 0;
}
