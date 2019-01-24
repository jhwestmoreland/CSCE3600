/*
	Jared Westmoreland
	11022685
	This program is very much broken
*/
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <time.h>
#define SOCKETNAME  "selectServerSocket"

//stuct
typedef struct{
int list;
int ticket_value;
char update[6];
}ticket;

//functions
void initial(ticket ticket1[20]);
void print(ticket ticket1[20]);
int ticket_pruchase(ticket ticket1[20], char res[1024]);
int ticket_give(int part, ticket ticket1[20], char res[1024]);

int main(int argc, char *argv[])
{
	//variables used
	ticket ticket1[20];
	char *good;
	int value = 0;
	char res[1024];
	char bad[] = "INVALID\n";
	char stuffed[] = "FULL\n";
    char buf[1024];		        
    int list;                         
    int first_connection;                        
    int second_connection;                        
	int leng;                        
    int max;                      
    int red;                      
    int redy;                     
    fd_set fds;                     
	struct sockaddr_in address;
	int addrlen = sizeof(address);

	if(argc < 2)
	{
		printf("usage: %s port\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	initial(ticket1);
	print(ticket1);
        //Remove any previous 
        unlink(SOCKETNAME);

        //Create the socket

        if ((list = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
        {
        	perror("socket");
        	exit(1);
        }

    //Create the address
	int number_for;
	number_for = atoi(argv[1]);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( number_for );
	leng = sizeof(address.sin_family);

    //Bind
	if (bind(list, (struct sockaddr *) &address, leng) < 0)
	{
			perror("bind");
			exit(1);
	}

	// Listen for connections
	if (listen(list, 5) < 0)
	{
			perror( "listen");
			exit(1);
	}


	//Accept
	if ((first_connection = accept(list, (struct sockaddr *) &address, &leng)) < 0)
	{
			perror("accept");
			exit(1);
	}

	// Accept
	if ((second_connection = accept(list, (struct sockaddr *) &address, &leng)) < 0)
	{
			perror("accept");
			exit(1);
	}
    max = (first_connection > second_connection ? first_connection : second_connection) + 1;
	while (1)
	{
        FD_ZERO(&fds);
        FD_SET(first_connection,&fds);
        FD_SET(second_connection,&fds);

        //Waits
        redy = select(max, &fds, (fd_set *) 0, (fd_set *) 0, (struct timeval *) 0);
       //read it and copy it to the other

        if( FD_ISSET(first_connection, &fds))
        {
		//Client1
        	red = recv(first_connection, buf, sizeof(buf), 0);
        	//terminate
        	if(red < 1)
		{
        		close(first_connection);
        		close(second_connection);
        		exit(0);
        	}

		//search buf for keywords
		strcat(res, "Client 1 ");
		good = strtok(buf, " ");
		if(strncmp(good, "BUY", 3) == 0)
		{
			strncat(res, good, 3);
			value = ticket_pruchase(ticket1, res);
        		if(value == 1)
			{
        			strcat(res, " failed\n");//returns Client1 BUY failed
				send(first_connection, stuffed, strlen(stuffed), 0);
				send(second_connection, stuffed, strlen(stuffed), 0);
        			send(first_connection, res, strlen(res), 0);
        		}
        		else
			{
				strcat(res, " ");
				strcat(res, res);
				strcat(res, "\n");
        			send(first_connection, res, strlen(res), 0);
        		}
        	}
		else if(strncmp(good, "RETURN", 6) == 0)
		{
			strncat(res, good, 6);
			good = strtok(NULL, " ");
			if(ticket_give(atoi(good), ticket1, res) == 1)
			{
				strcat(res, " failed\n");
				send(first_connection, res, strlen(res), 0);
			}
			else
			{
				strcat(res, " ");
				strcat(res, res);
				strcat(res, "\n");
				send(first_connection, res, strlen(res), 0);
			}
		}
		else
		{
			send(first_connection, bad, strlen(bad), 0);
		}
		print(ticket1);
	}


        if( FD_ISSET(second_connection, &fds))//if receive a message from client 2 send to client one
       	{
		//Client 2
        	red = recv(second_connection, buf, sizeof(buf), 0);
        	//terminate
        	if(red < 1)
		{
        		close(first_connection);
        		close(second_connection);
        		exit(0);
        	}
		//this basically accept or denies all the buys
		strcat(res, "Client 2 ");
        	good = strtok(buf, " ");
        	if(strncmp(good, "BUY", 3) == 0)
		{
        		strncat(res, good, 3);
        		value = ticket_pruchase(ticket1, res);
        			if(value == 1)
				{
        				strcat(res, " failed\n");//returns failed
        				send(first_connection, stuffed, strlen(stuffed), 0);
        				send(second_connection, stuffed, strlen(stuffed), 0);
        				send(second_connection, res, strlen(res), 0);
        			}
        			else
				{
        				strcat(res, " ");
        				strcat(res, res);
					strcat(res, "\n");
        				send(second_connection, res, strlen(res), 0);
        			}
        	}
        	else if(strncmp(good, "RETURN", 6) == 0)
		{
        		strncat(res, good, 6);
        		good = strtok(NULL, " ");
        		if(ticket_give(atoi(good), ticket1, res) == 1)
			{
        			strcat(res, " failed\n");
        			send(second_connection, res, strlen(res), 0);
        		}
        		else
			{
				strcat(res, " ");
        			strcat(res, res);
				strcat(res, "\n");
    				send(second_connection, res, strlen(res), 0);
    			}
    		}
    		print(ticket1);
    	}
    	}
}
//intial set up
void initial(ticket ticket1[20])
{
	int i = 0;
	srand(time(NULL));
	for(i = 0; i < 20; i++)
	{
	  	ticket1[i].list = i;
	  	ticket1[i].ticket_value = rand() % 89999 + 10000;
	  	strcpy(ticket1[i].update, "AVAIL");
 	}
}
//display for the server
void print(ticket ticket1[20])
{
	int j = 0;
	printf("[SERVER]: Database Table:\n");
	printf("-------------------------\n");
   	for(j = 0; j < 20; j++)
	{
   		printf("[Tkt# %d] %d : %s\n", ticket1[j].list, ticket1[j].ticket_value, ticket1[j].update);
   	}
	printf("-------------------------\n");
}
//user ticket buys
int ticket_pruchase(ticket ticket1[20], char res[1024])
{
	int z = 0;
	char num[5];
  	for(z = 0; z < 20; z++)
	{
   		if(strncmp(ticket1[z].update, "AVAIL", 5) == 0)
		{
     			strcpy(ticket1[z].update, "SOLD");
     			strcat(res, " ");
     			sprintf(res, "%d", ticket1[z].ticket_value);
     			return 0;
   		}
  	}
   	return 1;
}
//checks if avail
int ticket_give(int part, ticket ticket1[20], char res[1024])
{
	int t = 0;
   	for(t = 0; t < 20; t++)
	{
   		if(ticket1[t].ticket_value == part && strncmp(ticket1[t].update, "AVAIL", 5) == 0)
		{
     			return 1;
   		}
   		else if(ticket1[t].ticket_value == part)
		{
    			strcpy(ticket1[t].update, "AVAIL");
    			sprintf(res, "%d", ticket1[t].ticket_value);
			return 0;
   		}
  	}
}
