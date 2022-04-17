#ifndef __CUBPARSE_H__
#define __CUBPARSE_H__

#include "util.h"

typedef struct s_cubfile {
    char no_texture_path[1024];
    char so_texture_path[1024];
    char we_texture_path[1024];
    char ea_texture_path[1024];
    int color_ceil;
    int color_floor;
    char *map_data;
    int map_width;
    int map_height;
} t_cubfile;

t_cubfile* read_cubfile(int fd);
void destroy_cubfile(t_cubfile **cub);

void debug_print_cubfile(t_cubfile *cub);

#endif
