#include "print_page.h"
#include <stdio.h>
#include <err.h>

int main(int argc, char ** argv)
{
	if(argc <= 1)
		err(1,"%s\n","Give more arguments");
	else
	{
		printf("%d\n",argc);
		print_page("http://www.example.com",argc,(const char **)argv);
	}
}
