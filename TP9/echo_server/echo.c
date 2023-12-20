#include <stddef.h>
#include <stdio.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <err.h>


#define BUFFER_SIZE 512

void rewrite(int fd, const void *buf, size_t count)
{
	ssize_t e;
	while(count > 0)
	{
		e = write(fd,buf,count);
		count -= e;
	}
	if(e == -1)
		err(1,"%s","Error");
}

void echo(int fd_in, int fd_out)
{
	char buffer[BUFFER_SIZE];
	int r = -1;
	while(r != 0)
	{
		memset(&buffer,0,BUFFER_SIZE);
		r = read(fd_in,buffer, BUFFER_SIZE);
		if(r == -1)
			err(1,"%s","Error");
		else
			rewrite(fd_out,buffer,r);
	}
}
