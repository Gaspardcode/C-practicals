#include <stdio.h>
 #include <stdlib.h>
 #include <err.h>
 
 char* replace(const char* s, const char* from, const char* to);
 
 void freplace(char** s, const char* from, const char* to)
 {
     char* result = replace(*s, from, to);
     free(*s);
     *s = result;
 }
 
 int main(int argc, char** argv)
 {
     if (argc != 4)
         errx(EXIT_FAILURE, "%s",  "Usage: ./test <first_name> <last_name> <nick_name>");
 
     char str[] =
         "Hello (FIRST_NAME) (LAST_NAME)\n"
         "  * Your first name is: (FIRST_NAME)\n"
         "  * Your last name is: (LAST_NAME)\n"
         "  * Your nickname is: (NICKNAME)\n"
         "Good bye (FIRST_NAME) (LAST_NAME) (I mean (NICKNAME))\n";
 
     char* s = replace(str, "(FIRST_NAME)", argv[1]);
     freplace(&s, "(LAST_NAME)", argv[2]);
     freplace(&s, "(NICKNAME)", argv[3]);
 
     printf("%s", s);
 
     free(s);
     return EXIT_SUCCESS;
 }
