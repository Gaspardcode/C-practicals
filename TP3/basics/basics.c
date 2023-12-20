#define _GNU_SOURCE
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define ul (unsigned long)
unsigned long* array_fibo(size_t n)
{
	size_t l = sizeof(unsigned long);
	unsigned long * f = (unsigned long *) malloc(n * l);
	unsigned long a, b, c;
	a = b = 0;
	c = 1;
	for(size_t i = 0; i < n; i++)
	{
		f[i] = b;
		a = b;
		b = c;
		c += a;
	}
	return f;
}
 
char* str_toupper(const char* s)
{
	int n = 0;
	for(int i = 0; s[i] != 0; i++)
		n++;
	char * str = (char*) malloc((n + 1) * sizeof(char));
	for(int i = 0; s[i] != 0; i++)
	{
		//str = (char*) realloc(str,(i+1) * sizeof(char)); 
		str[i] = toupper((unsigned char) s[i]);
	}
	str[n] = 0;
	return str;
}
 
 unsigned char* array_pal_1(unsigned char* a, size_t len)
 {
	unsigned char * str = realloc(a,(2*len + 1)*sizeof(unsigned char));
	for(size_t i = 0; i < len; i++)
		str[len + i] = str[len - i - 1];
	str[2 * len] = 0;
	return str;
 }
 
 void array_pal_2(unsigned char** a, size_t len)
 {
 	*a = realloc((*a),(2*len + 1)*sizeof(unsigned char));
	for(size_t i = 0; i < len; i++)
		(*a)[len + i] = (*a)[len - i - 1];
	(*a)[2 * len] = 0;
 }
 
 size_t array_min(unsigned char* a, size_t len, unsigned char threshold, unsigned char** result)
 {
	size_t c = 0;
	*result = NULL;
	for(size_t i = 0; i < len; i++)
	{
		if (a[i] < threshold)
		{
			++c;
			*result = realloc((*result),(c)*sizeof(unsigned char));
			(*result)[c-1] = a[i];
		}
	}
	return c;
 }
 
 void str_checksum(char** s)
 {
	unsigned int c = 0;
	char* str;
 	for(int i = 0 ; (*s)[i] != 0; i++)
		c += (*s)[i];
	asprintf(&str, "%s (%X)\n",*s,c);
	free(*s);
	*s = str;
 }
