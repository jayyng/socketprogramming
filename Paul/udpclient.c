/* udpclient.c
 * ------------
 * Here's a very simple client
 * set the destination IP address below in inet_aton(), ie, the server's addr
 * eg, "192.168.1.173",  33333 is the server's port where udpserver is 
 * listening, you can change to any other port, but be sure to also
 * change the udpserver.c code to listen to the same port that udpclient
 * is goint to send to
 * run it, and it will send "Hello" to udpserver
 * NOTE -> udpserver must be listening before you run udpclient
 * you can run both client and server on the same machine
 * just set the destination IP below to "127.0.0.1". 
 * 
 *  - paul
 */

#include <sys/socket.h> //for socket(), sendto(), inet_aton()
#include <resolv.h>     //for socket(), sendto()
#include <netinet/in.h> //for htons() which works like atoi()

int main()
{
	struct sockaddr_in addr; //addr -> to store IP address and port
	int sd; //socket descriptor, like file descriptor

	/* must create socket before can talk */
	sd = socket(PF_INET, SOCK_DGRAM, 0); //internet, UDP, IP
	
	
	/* initialize the destination IP address and port */
	addr.sin_family = AF_INET;   //AF_INET is internet
	addr.sin_port = htons(33333); //something like atoi()
	inet_aton("127.0.0.1", &addr.sin_addr);//something like strcpy()
	
	
	/* Send message, '0' means normal */
	sendto(sd, "Hello", strlen("Hello"), 0, &addr, sizeof(addr));

	
	close(sd);
	return 0;
}
