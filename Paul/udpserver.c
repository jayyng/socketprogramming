/* udpserver.c
 * -----------
 * will listen on port 33333
 * you can change to any other port above 1024 but be sure
 * to change your udpclient.c to send to the new port
 * run udpserver, then run udpclient, 
 * udpclient will send "Hello"
 * udpserver receives it and prints messsage
 * NOTE-> you can run both udpserver and udpclient on same machine
 *
 * - paul
 */

#include <stdio.h>
#include <sys/socket.h> //for socket(), bind(), recvfrom(), sockaddr_in
#include <resolv.h>     //for socket(), bind(), recvfrom(), sockaddr_in
#include <netinet/in.h>
#define BUFSIZE 80	//set bigger num if you expect to recv longer strings

int main()
{	char buffer[BUFSIZE];
	struct sockaddr_in addr; // create an internet socket address struct 
	int sd, addr_size;
	
	/* init buffer to NULL so that u won't get junk when doing printf() */
	memset(buffer, 0, BUFSIZE); 
	
	/* must create socket, for communication  */
	sd = socket(PF_INET, SOCK_DGRAM, 0);//ie: Internet, UDP, IP

	/* initialize own IP address and port 
	 * INADDR_ANY will automatically be replaced with
	 * own IP address, eg, "127.0.0.1" if no NIC present
	 * the sockaddr_in has 3 members (4 actually), ie,
	 * socket internet family (sin_family),
	 * socket internet port (sin_port)
	 * socket address (sin_addr.s_addr)
	 * note -> sin_addr.s_addr is struct within a struct, real
	 * ugly*/
	addr.sin_family = AF_INET;     //ie, internet
	addr.sin_port = htons(33333);   //like atoi()
	addr.sin_addr.s_addr = INADDR_ANY;  

	/* must bind the address and port so that
	 * clients can send to it */
	bind(sd, &addr, sizeof(addr)); 
	
	
	/* recvfrom() will accept the client's message and store it in
	 * a string called "buffer"
	 * Because recvfrom()' last param is a pointer, we
	 * need to pass the addr's size indirectly.
	 * that's why we need  "addr_size" so that we can pass it's
	 * address in recvfrom()'s last param. 
	 * Note that we don't have to do this
	 * for sendto(), because sendto()'s address size param is
	 * type int 
	 * sendto() is used in udpclient.c */
	addr_size = sizeof(addr); 
	recvfrom(sd, buffer, BUFSIZE, 0, &addr, &addr_size);
		
	
	
	printf("Received -> %s\n", buffer);
			
	close(sd);
	return 0;
}