#include "so_long.h"

int	so_long()
{
	t_program params;
	
	params.mlx_pointer = mlx_init;
	params.window = mlx_new_window(mlx_pointer, width, height, name);

	mxl_loop(mlx_pointer);
}