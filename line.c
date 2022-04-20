#include "line.h"

void brassenham_low(t_fvec2, t_fvec2, void *meta, t_point_handler handler);
void brassenham_high(t_fvec2, t_fvec2, void *meta, t_point_handler handler);

void brassenham(t_fvec2 p1, t_fvec2 p2, void *meta, t_point_handler handler) {
    float dx = fabs(p1.x - p2.x);
    float dy = fabs(p1.y - p2.y);

    if (dx < dy)
        brassenham_low(p1, p2, meta, handler);
    else
        brassenham_high(p1, p2, meta, handler);
    
}

void brassenham_low(t_fvec2 p1, t_fvec2 p2, void *meta, t_point_handler handler)
{
    if (p1.x > p2.x)
        swap_fvec2(&p1, &p2);
    
    const float dy = (p2.y - p1.y) / (p2.x - p1.x);
    while (p1.x <= p2.x) {
        handler(make_ivec2(p1.x, p1.y), meta);
        p1.x += 1.0f;
        p1.y += dy;
    }
}

void brassenham_high(t_fvec2 p1, t_fvec2 p2, void *meta,t_point_handler handler)
{
    if (p1.y > p2.y)
        swap_fvec2(&p1, &p2);
    
    const float dx = (p2.x - p1.x) / (p2.y - p1.y);
    while (p1.y <= p2.y) {
        handler(make_ivec2(p1.x, p1.y), meta);
        p1.x += dx;
        p1.y += 1.0f;
    }
}
