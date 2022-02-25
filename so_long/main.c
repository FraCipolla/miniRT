/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 17:51:17 by mabasset          #+#    #+#             */
/*   Updated: 2022/02/25 13:18:46 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
static int	ft_hooks(int keycode, fdf *data)
{
	if (keycode == 53)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		exit(0);
	}
	return(0);
}

void	draw(fdf *data)
{
	int	row;
	int	col;
	int i;

	row = 0;
	while (row < data->height)
	{
		col = 0;
		while (col < data->width)
		{
			if (data->matrix[row][col] == '1')
			{
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->images.current_grass, col * data->img_width, row * data->img_height);
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->images.img_wall, col * data->img_width, row * data->img_height);
			}
			else if (data->matrix[row][col] == 'E')
			{
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->images.current_grass, col * data->img_width, row * data->img_height);
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->images.img_dog_1, col * data->img_width, row * data->img_height);
			}
			else
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->images.current_grass, col * data->img_width, row * data->img_height);
			col++;
		}
		row++;
		mlx_string_put(data->mlx_ptr, data->win_ptr, data->width, data->height, 15921152, "MOVE_COUNT:");
	}
}

/*int	deal_key(int key, fdf *data)
{
	ft_printf("%d\n", key);
	if (key == 126)
		data->shift_y -= 10;
	if (key == 125)
		data->shift_y += 10;
	if (key == 123)
		data->shift_x -= 10;
	if (key == 124)
		data->shift_x += 10;
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	draw(data);
	return (0);
}*/

int	main(int argc, char *argv[])
{
	fdf	data;

	data.frames = 0;
	if (argc == 2)
	{
		read_file(argv[1], &data);
		if (ft_checkmap(&data) == 0)
			ft_error("Map");
		ft_printstruct(&data);
		data.mlx_ptr = mlx_init();
		ft_open_images (&data);
		//ft_printf("%d\n", data.img_height);
		data.win_ptr = mlx_new_window(data.mlx_ptr, data.width * data.img_width, data.height * data.img_height, "FDF");
		//data.zoom = 20;
		draw(&data);
		mlx_key_hook(data.win_ptr, ft_hooks, &data);
		mlx_loop_hook(data.mlx_ptr, ft_updates, &data);
		mlx_loop(data.mlx_ptr);
		ft_freematrix(data.matrix, data.height);
	}
}
