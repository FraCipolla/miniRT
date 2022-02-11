#include "so_long.h"

int	game_init(t_game *game)
{
	game->mlx = mlx_init();
	game->window = mlx_new_window(game->mlx, ame->window_size.x + IMG_SIZE / 2, game->window_size.y, "so_long");

	mxl_loop(mlx_pointer);
}