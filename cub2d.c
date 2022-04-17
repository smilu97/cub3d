#include "cub2d.h"

int main(int argc, char** argv) {
	if (argc < 2) {
		printf("syntax: %s cubfile\n", argv[0]);
		return -1;
	}

	int fd = open(argv[1], O_RDONLY);
	t_cubfile *cub = read_cubfile(fd);
	close(fd);
	if (cub) {
		debug_print_cubfile(cub);
	}
	destroy_cubfile(&cub);
	
    // void *mlx;
	// void *mlx_win;

	// mlx = mlx_init();
	// mlx_win = mlx_new_window(mlx, 1280, 1024, "Hello world!");
	// mlx_loop(mlx);
}
