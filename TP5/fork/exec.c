#include <stdlib.h>
#include <unistd.h>
#include <err.h>

int main(int argc, char ** argv)
{
	if(argc < 2)
		errx(EXIT_FAILURE,"Usage: %s COMMAND [ARGUMENTS]...",argv[0]);
	char * cmd = argv[1];
	char ** options = malloc(argc);
	for(int i = 1; i < argc;++i)
		options[i-1] = argv[i];
	//if(fork() == 0)
	//{
	int stat = execvp(cmd,options);
	if(stat == -1)
		errx(EXIT_FAILURE,"%s","execvp() : No such file or directory" );
	//}
		return EXIT_SUCCESS;
}
