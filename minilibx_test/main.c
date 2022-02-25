#include <mlx.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "fdf.h"

void	ft_put_images(fdf *img)
{
	int	x;
	int	y;

	y = 0;
	while (y < img->height)
	{
		x = 0;
		//printf("BREAK\n");
		while (x < img->width)
		{
			//printf("BREAK\n");
			if (img->matrix[y][x] == 1)
				mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->wall, (x * 32), (y * 32));
			else
				mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->bg, (x * 32), (y * 32));
			x++;
		}
		y++;
	}
}

int	main(void)
{
	int		x;
	int		y;
	int 	c;
	int		i;
	fdf		img;

	read_file("map01.ber", &img);
	ft_printstruct(&img);
	img.mlx_ptr = mlx_init();
	img.win_ptr = mlx_new_window(img.mlx_ptr, img.width * 32, img.height * 32, "Hello world!");
	img.bg = mlx_xpm_file_to_image(img.mlx_ptr, "white.xpm", &c, &i);
	img.wall = mlx_xpm_file_to_image(img.mlx_ptr, "black.xpm", &x, &y);
	//mlx_put_image_to_window( )
	ft_put_images(&img);
	mlx_loop(img.mlx_ptr); 
}
