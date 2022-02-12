#include "so_long.h"

/* 	START MLX, OPENS WINDOW, OPENS IMAGES */
int	game_init(t_game *game)
{
	game->mlx = mlx_init();
	game->window = mlx_new_window(game->mlx, ame->window_size.x + IMG_SIZE / 2, game->window_size.y, "so_long");
	mlx_hook(game->window, 17, 0, end_program, game);
	open_images(game);
	game->white_panel = new_panel(game, new_color(254. 254. 2545. 0));
	game->red_panel = new_panel(game, new_color(197. 4. 4. 0));

	mxl_loop(mlx_pointer);
}