#ifndef __LINE_H__
#define __LINE_H__

#include <math.h>

#include "util.h"

typedef void (*t_point_handler)(t_ivec2, void*);

void brassenham(t_fvec2 p1, t_fvec2 p2, void *meta, t_point_handler handler);

#endif
