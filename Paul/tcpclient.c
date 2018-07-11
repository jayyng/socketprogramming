
/* tcpclient.c 
 * -----------
 * this is the TCP version of the udpclient.c
 * be sure to change the IP address in inet_aton() below to 
 * that of your server */

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

main()
{	
	int sd;
	struct sockaddr_in addr;
	
	sd = socket(PF_INET, SOCK_STREAM, 0);
	memset(&addr,0,sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(33333);
	
	/* change this to your server's IP */
	inet_aton("127.0.0.1", &addr.sin_addr);
	
	/* TCP is connection-oriented, that's why must connect() */
	connect(sd, &addr, sizeof(addr)); 
	
	/* TCP uses send(), UDP uses sendto() */
	send(sd, "Hello" , strlen("Hello"), 0);

	
	close(sd);
}
