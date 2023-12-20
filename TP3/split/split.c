#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include <stdio.h> 

 void words_free(char** words)
 {
     // Frees the strings.
     for (size_t i = 0; words[i]; i++)
         free(words[i]);
 
     // Frees the string pointers.
     free(words);
 }
 
 char** split(char* s)
 {
	char **str = calloc(1,8);
        str[0] = calloc(1,1);
        unsigned int c = 0;
        unsigned int p = 0;
        for(int i = 0; s[i] != 0; ++i)
        {
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
