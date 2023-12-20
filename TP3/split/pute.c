#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char** split(char* s)
 {
	char **str = calloc(1,8);
	str[0] = calloc(1,1);
	int c = 0;
	int p = 0;
	for(int i = 0; s[i] != 0; i++)
	{
		//printf("%c",s[i]);
		if(s[i] == ' ')
		{
			if(c != 0)
			{
				str[p][c] = 0;
				p++;
				str = realloc(str, (p+1)*8);
				str[p] = calloc(1,1);
				c = 0;
			}
		}
		else
		{
			c++;
			str[p] = realloc(str[p], (c+1));
			str[p][c-1] = s[i];
		}
	}
	if(c != 0)
	{	
		str[p][c] = 0;
		p++;
		str = realloc(str, (p+1)*8);
		str[p] = calloc(1,1);
	}
	return str;
}
int main()
{
	/*
	char ** s = calloc(1, 1);
	s = realloc(s, 24);
	char * w = "Hello World";
	s[0] = calloc(1,1);
	s[0] = realloc(s[0], 30); 
	s[0][12] = 0; 
	//strcat(s[0],"holaaaaa");
	s[1] = calloc(1,1);
	s[1][0] = 0;
	s[2] = calloc(10,1);
	strcat(s[2],"HULU");
	printf("%s\n",s[0]);
	printf("%s\n",s[1]);
	printf("%s\n",s[2]);
	free(s[0]);
	free(s[1]);
	free(s[2]);
	free(s);
	*/
	char ** s = split("Hello world pute    haha    ");
	printf("%s\n",s[0]);
	printf("%s\n",s[1]);
	printf("%s\n",s[2]);
	printf("%s\n",s[3]);
	printf("%s\n",s[4]);
	free(s[0]);
	free(s[1]);
	free(s[2]);
	free(s[3]);
	free(s[4]);
	free(s);
	return EXIT_SUCCESS;
}
