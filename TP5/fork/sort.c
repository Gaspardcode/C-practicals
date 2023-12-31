#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <err.h>
#include <sys/wait.h>
#include <time.h>

#define PRINT(fmt_, ...) printf("%u: " fmt_ "\n", \
		getpid() __VA_OPT__(,) __VA_ARGS__);

void random_fill(int tab[], size_t len)
{
 for (int *cur  = tab; cur != tab +len; ++cur)
	 *cur = random() % 1024;
}

void swap(int *a, int *b)
{
	int c = *a;
	*a = *b;
	*b = c;
}

const char* is_sorted(int tab[], size_t len)
{
	size_t j = 1;
	
	while(j < len && tab[j-1] <= tab[j])
		j++;

	return j == len ? "Yes" : "No";
}

void sort1(int tab[], size_t len)
{
	for(size_t i = 0; i < len; ++i)
	{
		size_t min = i;

		for(size_t j = i + 1; j < len ; ++j)
			if (tab[j] < tab[min])
                	min = j;

        	swap(tab + i, tab + min);
	}
}

void sort2(int tab[], size_t len)
{

	int move = 1;

	for(size_t i = 0; i < len && move; ++i)
	{
		move = 0;
		for (size_t j = 0; j < len - i -1; ++j)
		{
			if(tab[j] > tab[j + 1])
			{
				move = 1;
				swap(tab + j, tab + j + 1);
			}
		}
	}
}

double diff_timespec(const struct timespec* t1, const struct timespec* t0)
{
	double second = difftime(t1->tv_sec, t0->tv_sec);
	return second + ((double)t1->tv_nsec - (double)t0->tv_nsec) / 1e9;
}
int main(int argc, char** argv)
{
	if(argc != 2)
	errx(EXIT_FAILURE, "Usage : %s ARRAY_SIZE (from 1 to 100000)", argv[0]);

	size_t size = strtoul(argv[1], NULL, 10);
	if (size == 0 || size > 100000)
		errx(EXIT_FAILURE, "The argument is not valid.");
	int a[size];
	PRINT("Sorted :%s", is_sorted(a, size));

	struct timespec t0;
	struct timespec t1;
	struct timespec t2;
	int state1,state2;
	clock_gettime(CLOCK_REALTIME,&t0);
	int id = fork();

	if (id == -1)
	{
		return EXIT_FAILURE;
	}
	else if(id)
	{
		wait(&state1);
		clock_gettime(CLOCK_REALTIME,&t1);
		PRINT("time 1: %lfs",diff_timespec(&t1,&t0));
		id = fork();
		if(id)
		{
			wait(&state2);
			clock_gettime(CLOCK_REALTIME,&t2);
			PRINT("time 2: %lfs",diff_timespec(&t2,&t0));
		}
		else
		{
			sort2(a,size);
			PRINT("Sorted 2 :%s", is_sorted(a, size));
		}
	}
	else
	{
		sort1(a,size);
		PRINT("Sorted 1 :%s", is_sorted(a, size));
	}

	return EXIT_SUCCESS;
}
