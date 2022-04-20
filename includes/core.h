#ifndef __CORE_H__
#define __CORE_H__

/** standard libraries **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cubparse.h"

/** typedefs **/

/** structs **/

typedef struct s_ray {
    t_fvec2 origin;
    float angle; // radian
} t_ray;

typedef struct s_ray_particle {
    t_fvec2 pos;
    t_fvec2 delta;
} t_ray_particle;

typedef struct s_wall {
    t_ivec2 p1;
    t_ivec2 p2;
    void *meta;
} t_wall;

/** functions **/

/** constants **/

#endif
