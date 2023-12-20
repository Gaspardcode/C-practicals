#ifndef PRINT_PAGE_H
#define PRINT_PAGE_H

#include <stddef.h>

void rewrite(int fd, const void *buf, size_t count);

void parse_url(const char *url, char **host, char **path);
char *build_query(const char *host, const char *path, size_t *len);

void write_request(int fd, const char *host, const char *path, size_t argc,
                   const char **argv);
void print_page(const char *url, size_t argc, const char **argv);

#endif
