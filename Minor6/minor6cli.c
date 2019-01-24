/*
	Jared Westmoreland
	11022685
	This program is very much broken
*/
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/un.h>
#include <sys/time.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#define SOCKETNAME  "selectServerSocket"

int main(int argc, char *argv[])
{
    	int s;          /* This end of connection*/
    	int len;        /* length of sockaddr */
    	int nread;      /* return from read() */
    	int nready;     /* # fd's ready. */
    	int maxfd;      /* fd's 0 to maxfd-1 checked. */
    	char buf[1024];
    	fd_set fds;     /* set of file descriptors to check. */
	struct sockaddr_in address;
	int sock = 0, valread;
	struct sockaddr_in serv_addr;
	char *hello;


	if(argc < 2)
	{
		printf("usage: %s port", argv[0]);
		exit(1);
	}

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    	{
                perror("socket");
                exit(1);
        }

        /*Create the address of the server.*/
	memset(&serv_addr, 0, sizeof(serv_addr));

	int number;
	number=atoi(argv[2]);

	serv_addr.sin_family = AF_INET;
    	serv_addr.sin_port = htons(number);

	    // Convert IPv4 and IPv6 addresses from text to binary form
    	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
    	{
        	printf("\nInvalid address/ Address not supported \n");
        	return -1;
    	}
    	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    	{
        	printf("\nConnection Failed \n");
     		return -1;
    	}

		//I basically grabbed Dr. Thompsons because I accidentally deleted mine
		//I know it doesn't work because I no longer had any time to complete this
        maxfd = s + 1;
        while(1)
		{
		 /* Set up polling. */
                FD_ZERO(&fds);
                FD_SET(s,&fds);
                FD_SET(0,&fds);

                /* Wait for some input. */
                nready = select(maxfd, &fds, (fd_set *) 0, (fd_set *) 0,
                                (struct timeval *) 0);

                /* If either device has some input,
                   read it and copy it to the other. */

                if( FD_ISSET(s, &fds))
                {
                        nread = recv(s, buf, sizeof(buf), 0);
                        /* If error or eof, terminate. */
                        if(nread < 1)
			{
                                close(s);
                                exit(0);
                        }
                        send(s, buf, nread,0);
                }

                if( FD_ISSET(0, &fds))
                {
                        nread = read(0, buf, sizeof(buf));
                        /* If error or eof, terminate. */
                        if(nread < 1){
                                close(s);
                                exit(0);
                        }
                        send( s, buf, nread, 0); 
                }

        }
}

