#ifndef __UTIL_H__
#define __UTIL_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

typedef struct s_string {
    char *buf;
    int capacity;
    int length;
} t_string;

typedef struct s_arraylist {
    void **buf;
    int capacity;
    int length;
} t_arraylist;

int max2i(int, int);
int min2i(int, int);

int parse_int(const char *s, int len);

t_string make_string();
t_string ref_string(t_string *src);
t_string sub_string(t_string *src, int from, int length);
void clean_string(t_string *s);
void destroy_string(t_string *s);
void append_string(t_string *s, char ch);

void readline(t_string *line, int fd);
void readall(t_string *s, int fd);

t_string trim_left(t_string *src, char *blacklist);
t_string trim_right(t_string *src, char *blacklist);
t_string trim(t_string *src, char *blacklist);

t_arraylist make_arraylist();
void clean_arraylist(t_arraylist *array);
void destroy_arraylist(t_arraylist *array);
void append_arraylist(t_arraylist *array, void *el);

#endif
