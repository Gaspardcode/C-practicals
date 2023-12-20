#define _GNU_SOURCE

#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>
#include <unistd.h>

const size_t BUFFER_SIZE = 32;

void rewrite(int fd, const void *buf, size_t count)
{
	ssize_t e;
	while(count > 0)
	{
		e = write(fd,buf,count);
		count -= e;
	}
	if(e == -1)
		err(1,"%s", "Error rewrite");
}

void parse_url(const char *url, char **host, char **path)
{
	size_t i = 0;
	while(url[i] && url[i] != '/')
		i++;
	*host = strndup(url,i);
	size_t len = strlen(url) - i;
	if(len <= 0)
	{
		*path = "/";
	}
	else
		*path = strdup(&url[i]);
}

char *build_query(const char *host, const char *path, size_t *len)
{
	char *request;
	int e = asprintf(&request,"GET %s HTTP/1.0\r\nHost: %s\r\n",path,host);
	*len = strlen(request);
	if(e == -1)
		err(1,"%s", "Error build_query");
	else
		return request;
}

void write_request(int fd, const char *host, const char *path, size_t argc,
                   const char **argv)
{
	size_t *len = malloc(sizeof(int));
	char *request = build_query(host,path,len);
	printf("%s",request);
	rewrite(fd,request,*len);
	char * l = "\r\n";
	for(int i = 3; i < argc; i += 2)
	{
		size_t j = 0;
		size_t slen = strlen(argv[i]);
		while(argv[i][j] && argv[i][j] != ':')
			j++;
		if(j < slen)
		{
			request = calloc(strlen(argv[i]) + 2,1);
			strcat(request,argv[i]);
			strcat(request,l);
			printf("%s",request);
			rewrite(fd,request,slen);
		}
	}
	printf("%s",l);
	rewrite(fd,l,2);
	free(request);
	free(len);
}

void print_page(const char *url, size_t argc, const char **argv)
{
    char buffer[BUFFER_SIZE];

    struct addrinfo hints;

    memset(&hints, 0, sizeof(hints));

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    char *host = NULL;
    char *path = NULL;
    struct addrinfo *result;
    parse_url(argv[1],&host,&path);
    int e = getaddrinfo(host,"80",&hints,&result);

    if(e)
    {
	printf("error: %s\n",gai_strerror(e));
	exit(EXIT_FAILURE);
    }

    int sfd;
    struct addrinfo* p;
    for (p = result; p != NULL; p = p->ai_next)
    {
	sfd = socket(p->ai_family,
			p->ai_socktype,
			p->ai_protocol);
	if(sfd != -1)
	{
		e = connect(sfd,p->ai_addr,p->ai_addrlen);
		if(e != -1)
			break;
		else
			close(sfd);
	}
    }
    //freeaddrinfo(result);

    if(p == NULL)
	    errx(EXIT_FAILURE,"Couldn't connect");

    write_request(sfd, host,path,argc,argv);
    size_t a = 1;
    while(a > 0)
    {
	    memset(&buffer,0,BUFFER_SIZE);
	    a = read(sfd,buffer,BUFFER_SIZE);
	    printf("%s",buffer);
    }
    if(a == -1)
	    err(1,"%s","Error read");
    close(sfd);
    freeaddrinfo(p);
    //free(host);
    //free(path);
}
