/* multi_tcpserver.c 
 * -----------------
 * this is a multitasking server, using processes.   
 * it can accept connections from multiple clients.
 * use tcpclient to connect.
 *  - paul */  

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>  /* needed by fork() */
#define BUFSIZE 80

main()
{	
	int sd, clientsd, addr_len, PID;
	struct sockaddr_in addr;
	char buf[BUFSIZE];
	
	sd = socket(PF_INET, SOCK_STREAM, 0);
	memset(&addr,0,sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(33333);
	addr.sin_addr.s_addr = INADDR_ANY;

	bind(sd, &addr, sizeof(addr) );
	
	/* listen on socket, and can queue 20 connect requests */
	listen(sd, 20);


	while(1){	
		addr_len = sizeof(addr);
		clientsd = accept(sd, &addr, &addr_len); 
	
		/* 
		 * After fork(), there will be two identical processess, ie
		 * 1. the parent -> with it's fork() will return a positive
		 *    integer eg, 1689 which becomes the child's pid
		 * 2. the child -> with it's fork() which  returns 0
		 * Therefore we test the return value to differentiate the 
		 * parent from the child. If it is the parent, we close
		 * the new client socket ("clientsd"). 
		 * If it is the child we close the main socket ("sd").
		 */ 	
		PID = fork(); 
		if(PID==0){	/* a child since, pid==0 */
			close(sd);/*child don't need to listen on original socket*/
			memset(buf,0,BUFSIZE);
	
			recv(clientsd, buf, BUFSIZE, 0);

			/* print the child's pid, and the "Hello" message
			 * from tcpclient */
			printf("Client %d -> %s\n", getpid(), buf);
			close(clientsd);
			exit(0);
		}
		else    /* ie pid is above 0, therefore a parent */
			close(clientsd); /*parent don't need clientsd
					  since it's job is to listen on 
					  main socket, ie sd.*/ 
	}
	
}
