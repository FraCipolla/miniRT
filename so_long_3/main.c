/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 17:51:17 by mabasset          #+#    #+#             */
/*   Updated: 2022/03/09 17:15:21 by mcipolla         ###   ########.fr       */
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
	if (keycode == 13)
		move_up(data);
	else if (keycode == 1)
		move_down(data);
	else if (keycode == 0)
		move_left(data);
	else if (keycode == 2)
		move_right(data);
	draw(data);
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
			if (data->matrix[row][col] == 'P')
			{
				data->y = row;
				data->x = col;
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->images.current_grass, col * data->img_width, row * data->img_height);
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->images.current_char, col * data->img_width, row * data->img_height);
			}
			if (data->matrix[row][col] == '1')
			{
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->images.current_grass, col * data->img_width, row * data->img_height);
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->images.img_wall, col * data->img_width, row * data->img_height);
			}
			if (data->matrix[row][col] == 'M')
			{
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->images.current_grass, col * data->img_width, row * data->img_height);
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->images.current_dog, col * data->img_width, row * data->img_height);
			}
			if (data->matrix[row][col] == 'C')
			{
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->images.current_grass, col * data->img_width, row * data->img_height);
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->images.img_coll, col * data->img_width, row * data->img_height);
			}
			if (data->matrix[row][col] == 'E')
			{
				data->gx = col;
				if (data->c == 0)
					mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->images.img_escl, col * data->img_width, (row * data->img_height - 64));
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->images.current_grass, col * data->img_width, row * data->img_height);
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->images.current_exit, col * data->img_width, row * data->img_height);
			}
			if (data->matrix[row][col] == '0')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->images.current_grass, col * data->img_width, row * data->img_height);
			col++;
		}
		row++;
		if (data->c > 0)
				mlx_string_put(data->mlx_ptr, data->win_ptr, data->width * 16, data->height * 58, 16777215, "COLLECT ALL APPLES TO END THE LEVEL");
		else
			mlx_string_put(data->mlx_ptr, data->win_ptr, data->width * 16, data->height * 58, 16777215, "GG, NOW BRINGS THE APPLES TO THE GRANNY!");
		mlx_string_put(data->mlx_ptr, data->win_ptr, data->width, data->height, 16777215, "MOVES");
		mlx_string_put(data->mlx_ptr, data->win_ptr, data->width * 6, data->height, 16777215, ft_itoa(data->move_count));
	}
}

int	main(int argc, char *argv[])
{
	fdf	data;

	data.grass_frames = 0;
	data.dog_frames = 0;
	data.char_frames = 0;
	data.move_count = 0;
	if (argc == 2)
	{
		read_file(argv[1], &data);
		if (ft_checkmap(&data) == 0)
			ft_error("Map");
		ft_printstruct(&data);
		data.mlx_ptr = mlx_init();
		ft_open_images (&data);
		data.win_ptr = mlx_new_window(data.mlx_ptr, data.width * data.img_width, data.height * data.img_height, "so_long");
		data.images.current_grass = data.images.img_grass_1;
		data.images.current_dog = data.images.img_dog_1;
		data.images.current_char = data.images.img_char_1;
		data.images.current_exit = data.images.img_exit_1;
		data.images.part_an = 0;
		draw(&data);
		mlx_key_hook(data.win_ptr, ft_hooks, &data);
		mlx_loop_hook(data.mlx_ptr, ft_updates, &data);
		mlx_loop(data.mlx_ptr);
		ft_freematrix(data.matrix, data.height);
	}
}
