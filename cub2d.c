#include "cub2d.h"

int main(int argc, char** argv) {
	if (argc < 2) {
		printf("syntax: %s cubfile\n", argv[0]);
		return -1;
	}
	
    t_env env = make_env(500, 500, "Test");

	draw_line(&env.screen, make_fvec2(0, 0), make_fvec2(100, 100), 0xFF0000, 0xFF);
	
	flush_screen(&env);
	
	mlx_loop(env.mlx);
}
