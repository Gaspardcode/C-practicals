#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include <err.h>
#include "echo.h"

int main(int argc, char** argv)
{
    if (argc != 2)
        errx(EXIT_FAILURE, "Usage:\n"
            "Arg 1 = Port number (e.g. 2048)");

    struct addrinfo hints;

    memset(&hints,0,sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    struct addrinfo *result;

    int e = getaddrinfo(NULL,argv[1],&hints,&result);

    if(e)
    {
	printf("error: %s\n",gai_strerror(e));
	exit(EXIT_FAILURE);
    }

    int sfd;
    struct addrinfo *p = NULL;
    for(p = result; p != NULL; p = p->ai_next)
    {
	sfd = socket(p->ai_family,p->ai_socktype,p->ai_protocol);
	if(sfd != -1)
	{
		int optval = 1;
		setsockopt(sfd,SOL_SOCKET,SO_REUSEADDR,
				&optval,sizeof(int));
		e = bind(sfd,p->ai_addr,p->ai_addrlen);
		if(e == 0)
			break;
		else
			close(sfd);
	}
    }

    //FREE *result
    
    if(p == NULL)
	    errx(EXIT_FAILURE,"Couldn't connect");

    e = listen(sfd,5);

    if(e == -1)
    {
	close(sfd);
	errx(EXIT_FAILURE,"listen()");
    }

    while(1)
    {
	printf("Server waiting for connection(s)\n");

	int cfd = accept(sfd,NULL,NULL);

	if(cfd == -1)
		errx(EXIT_FAILURE,"accept()");
	else
	{
		printf("Connection successful !\n");
		echo(cfd,cfd);
		close(cfd);
		close(sfd);
	}

    }
}
