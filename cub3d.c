#include "cub3d.h"

int main(int argc, char** argv) {
    void *mlx;
	void *mlx_win;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1280, 1024, "Hello world!");
	mlx_loop(mlx);
}
