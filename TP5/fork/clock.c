#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <err.h>
#include <sys/wait.h>

double diff_timespec(const struct timespec* t1, const struct timespec* t0)
{
    double second = difftime(t1->tv_sec, t0->tv_sec);
    return second + ((double)t1->tv_nsec - (double)t0->tv_nsec) / 1e9;
}

int main(int argc, char** argv)
{
	if(argc == 1)
		errx(EXIT_FAILURE,"Usage: %s COMMAND [ARGUMENTS]...",argv[0]);
	char * cmd = argv[1];
	char ** options = malloc(argc);
	for(int i = 1; i < argc;++i)
		options[i-1] = argv[i];
	struct timespec t0;
	struct timespec t1;
	clock_gettime(CLOCK_REALTIME,&t0);
	int status;
	int useless;
	if(fork())
	{
		wait(&status);
		clock_gettime(CLOCK_REALTIME,&t1);
		printf("time = %lfs\n",diff_timespec(&t1,&t0));
	}
	else
	{
		useless = execvp(cmd,options);
		if(useless == -1)
			errx(EXIT_FAILURE,"%s","execvp() : No such file or directory" );
	}
	return WEXITSTATUS(status);
}
