#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <err.h>

const size_t BUFFER_SIZE = 32;

int main(int argc, char** argv)
{
	if(argc < 3)
		errx(EXIT_FAILURE, "Usage: %s FILE COMMAND [ARGUMENTS]...", argv[0]);
	int p[2], pid;
	pipe(p);
	st1 = open(argv[1],_RDONLY);
	if((pid = fork()))
	{
	}
	else if (pid == 0)
	{
		close(p[0]);
		//write();
	}
	else
	{}
	return EXIT_SUCCESS;
}
