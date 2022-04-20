#ifndef __UTIL_H__
#define __UTIL_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>

typedef struct s_fvec4 {
    float x;
    float y;
    float z;
    float w;
} t_fvec4;

typedef struct s_fvec2 {
    float x;
    float y;
} t_fvec2;

typedef struct s_ivec2 {
    int x;
    int y;
} t_ivec2;

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

t_ivec2 make_ivec2(int x, int y);
t_fvec2 make_fvec2(float x, float y);

t_fvec4 color_to_fvec4(int color);
int fvec4_to_color(t_fvec4 v);

t_fvec4 add_fvec4(t_fvec4 v1, t_fvec4 v2);
t_fvec2 sub_fvec2(t_fvec2 v1, t_fvec2 v2);
t_fvec4 mul_fvec4_f(t_fvec4 v, float f);
t_fvec4 interpolate_fvec4(t_fvec4 v1, t_fvec4 v2, float w);
float distance_fvec2(t_fvec2 v);
float rev_interpolate_fvec2(t_fvec2 t, t_fvec2 p1, t_fvec2 p2);

void swap_fvec2(t_fvec2 *p1, t_fvec2 *p2);

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
