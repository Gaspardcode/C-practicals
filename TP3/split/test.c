#include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <err.h>
 
 char** split(char* s);
 void words_free(char** words);
 char * app(char * str1, char * str2);  
 int main(int argc, char** argv)
 {
     if (argc != 2)
         errx(EXIT_FAILURE, "%s",  "Usage: ./test <string>");
 
     char** words = split(argv[1]);
 
     for (size_t i = 0; words[i]; i++)
         printf("word %02zu: %s\n", i, words[i]);
 
     words_free(words);
 
     return EXIT_SUCCESS;
 }
