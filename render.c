#include "render.h"

t_image make_image(t_env *env, int width, int height) {
    t_image img;
    img.handler = mlx_new_image(env->mlx, width, height);
    img.data = mlx_get_data_addr(
        img.handler,
        &img.bits_per_pixel,
        &img.line_length,
        &img.endian
    );
    return img;
}

int* get_pixel(t_image *img, int x, int y) {
    const int offset = y * img->line_length + x * (img->bits_per_pixel / 8);
    return (int*) (img->data + offset);
}

t_env make_env(int width, int height, char* title) {
    t_env env;
    env.screen_width = width;
    env.screen_height = height;
    env.mlx = mlx_init();
    env.win = mlx_new_window(env.mlx, width, height, title);
    env.screen = make_image(&env, width, height);
    return env;
}

void flush_screen(t_env *env) {
    mlx_put_image_to_window(env->mlx, env->win, env->screen.handler, 0, 0);
}

void draw_line_handler(t_ivec2 p, void *args_) {
    t_draw_line_args *args = (t_draw_line_args*) args_;
    t_fvec2 fp = make_fvec2(p.x, p.y);
    float w = rev_interpolate_fvec2(fp, args->p1, args->p2);
    const int color = fvec4_to_color(interpolate_fvec4(args->c1, args->c2, w));
    *get_pixel(args->img, p.x, p.y) = color;
}

t_draw_line_args make_draw_line_args(t_image *img, t_fvec2 p1, t_fvec2 p2, int c1, int c2) {
    t_draw_line_args args;
    args.img = img;
    args.p1 = p1;
    args.p2 = p2;
    args.c1 = color_to_fvec4(c1);
    args.c2 = color_to_fvec4(c2);
    return args;
}

void draw_line(t_image *img, t_fvec2 p1, t_fvec2 p2, int c1, int c2) {
    t_draw_line_args args = make_draw_line_args(img, p1, p2, c1, c2);
    brassenham(args.p1, args.p2, &args, draw_line_handler);
}
