#ifndef __RENDER_H__
#define __RENDER_H__

/** standard libraries **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mlx.h"
#include "util.h"
#include "line.h"

/** structs **/

typedef struct s_image {
    void *handler;
    char *data;
    int bits_per_pixel;
    int line_length;
    int endian;
} t_image;

typedef struct s_env {
    void *mlx;
    void *win;
    t_image screen;
    int screen_width;
    int screen_height;
} t_env;

typedef struct s_draw_line_args {
    t_image *img;
    t_fvec2 p1;
    t_fvec2 p2;
    t_fvec4 c1;
    t_fvec4 c2;
} t_draw_line_args;

t_image make_image(t_env *env, int width, int height);
int* get_pixel(t_image *img, int x, int y);
t_env make_env(int screen_width, int screen_height, char*);
void flush_screen(t_env *env);

void draw_line(t_image *img, t_fvec2 p1, t_fvec2 p2, int c1, int c2);

/** functions **/

#endif
