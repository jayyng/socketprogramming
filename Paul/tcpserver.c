
/* tcpserver.c 
 * -----------
 * this is the TCP version of udpserver.c  
 * the parts which are different are commented below
 *  - paul */  

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#define BUFSIZE 80

main()
{	
	int sd, clientsd,addr_len;
	struct sockaddr_in addr;
	char buf[BUFSIZE];
	
	sd = socket(PF_INET, SOCK_STREAM, 0);

	int one = 1; 
	// SOL_SOCKET = socket options, one = 1 means enable
	setsockopt(sd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &one, sizeof(one));

	memset(&addr,0,sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(33333);
	addr.sin_addr.s_addr = INADDR_ANY;

	bind(sd, &addr, sizeof(addr) );
	
	/* listen on socket, and can queue 20 connect requests */
	listen(sd, 20);
	
	/* addr_len is merely to store sizeof addr so that we can
	 * pass the address of addr to accept, because the third
	 * param of accept() is a pointer 
	 * Note: for connect(), third param is integer */
	addr_len = sizeof(addr);
	
	/* because TCP is connection-oriented, must do accept()
	 * it will return a new socket, and will reuse the addr struct
	 * that was defined above, bind() doesn't need it anymore.
	 * Alternatively, yu can define another sockaddr_in, eg
	 * struct sockaddr_in clientaddr, but it is not necessary */
	clientsd = accept(sd, &addr, &addr_len); 
	
	memset(buf,0,BUFSIZE);
	
	/* TCP uses recv(), UDP uses recvfrom() */
	recv(clientsd, buf, BUFSIZE, 0);
	printf("Client-> %s\n", buf);
		
		
	close(clientsd);
	close(sd);
}
