#include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <err.h>
 #include "basics.h"
 
 void exit_help()
 {
     char help[] =
         "Usage:\n"
         "--fibo <n (1-94)>\n"
         "--toupper <string>\n"
         "--pal1 <seed (1-99)> <len (1-20)>\n"
         "--pal2 <seed (1-99)> <len (1-20)>\n"
         "--min\n"
         "--checksum <string>";
 
     errx(EXIT_FAILURE, "%s", help);
 }
 
 void test_fibo(int argc, char** argv)
 {
     if (argc != 3)
         exit_help();
 
     size_t n = strtoul(argv[2], NULL, 10);
 
     if (n < 1 || n > 94)
         exit_help();
 
     unsigned long* fibo = array_fibo(n);
 
     for (size_t i = 0; i < n; i++)
         printf("fibo[%zu] = %lu\n", i, fibo[i]);
 
     free(fibo);
 }
 
 void test_toupper(int argc, char** argv)
 {
     if (argc != 3)
         exit_help();
 
     char* result = str_toupper(argv[2]);
 
     printf("%s\n", argv[2]);
     printf("%s\n", result);
 
     free(result);
 }
 
 void array_print(unsigned char* a, size_t len)
 {
     if (a == NULL)
     {
         printf("NULL (len = %zu)\n", len);
         return;
     }
 
     printf("{");
     for (size_t i = 0; i < len; i++)
         printf(" %hhu", a[i]);
     printf(" }\n");
 }
 
 unsigned char* array_rand(size_t n)
 {
     unsigned char* a = malloc(n * sizeof(unsigned char));
 
     for (size_t i = 0; i < n; i++)
         a[i] = rand() % 100;
 
     return a;
 }
 
 void nl()
 {
     printf("\n");
 }
 
 void _test_min(unsigned char* a, size_t len, unsigned char threshold, unsigned char** r)
 {
     printf("a = ");
     array_print(a, len);
     size_t min_len = array_min(a, len, threshold, r);
     printf("array_min(a, %zu, %hhu, &r)\n", len, threshold);
     printf("r = ");
     array_print(*r, min_len);
     free(*r);
 }
 
 void test_min()
 {
     unsigned char* r;
 
     unsigned char a0[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
     unsigned char a1[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
     unsigned char a2[] = { 0, 1, 2, 4, 5, 4, 3, 2, 1, 0 };
     unsigned char a3[] = { 5, 6, 5, 6, 5, 6, 5, 6, 5, 6 };
 
     _test_min(a0, sizeof(a0), 5, &r); nl();
     _test_min(a0, sizeof(a0), 0, &r); nl();
     _test_min(a0, sizeof(a0), 9, &r); nl();
     _test_min(a1, sizeof(a1), 3, &r); nl();
     _test_min(a2, sizeof(a2), 3, &r); nl();
     _test_min(a3, sizeof(a3), 6, &r); nl();
 }
 
 void test_pal(int argc, char** argv, int mode)
 {
     if (argc != 4)
         exit_help();
 
     size_t seed = strtoul(argv[2], NULL, 10);
     size_t len = strtoul(argv[3], NULL, 10);
 
     if (seed < 1 || seed > 99 || len < 1 || len > 20)
         exit_help();
 
     srand(seed);
     unsigned char* a = array_rand(len);
 
     printf("a = ");
     array_print(a, len);
 
     if (mode == 1)
     {
         a = array_pal_1(a, len);
         printf("a = array_pal(a, %zu)\n", len);
     }
 
     else
     {
         array_pal_2(&a, len);
         printf("array_pal(&a, %zu)\n", len);
     }
 
     printf("a = ");
     array_print(a, 2 * len);
 
     free(a);
 }
 
 void test_checksum(int argc, char** argv)
 {
     if (argc != 3)
         exit_help();
 
     size_t len = strlen(argv[2]);
 
     char* str = malloc(len * sizeof(char) + 1);
 
     strcpy(str, argv[2]);
 
     str_checksum(&str);
     printf("%s\n", str);
 
     free(str);
 }
 
 int main(int argc, char** argv)
 {
     if (argc == 1)
         exit_help();

     if (strcmp(argv[1], "--fibo") == 0)
         test_fibo(argc, argv);
     else if (strcmp(argv[1], "--toupper") == 0)
         test_toupper(argc, argv);
     else if (strcmp(argv[1], "--pal1") == 0)
         test_pal(argc, argv, 1);
     else if (strcmp(argv[1], "--pal2") == 0)
         test_pal(argc, argv, 2);
     else if (strcmp(argv[1], "--min") == 0)
         test_min();
     else if (strcmp(argv[1], "--checksum") == 0)
         test_checksum(argc, argv);
     else
         exit_help();

     return EXIT_SUCCESS;
}
