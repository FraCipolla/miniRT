/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 17:51:17 by mabasset          #+#    #+#             */
/*   Updated: 2022/03/12 15:14:14 by mcipolla         ###   ########.fr       */
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
	return (0);
}

void	draw2(fdf *data, int row, int col)
{
	t_enemy	*enemy_list;
	
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->images.current_grass, col * 64, row * 64);
	if (data->matrix[row][col] == 'P')
	{
		data->y = row;
		data->x = col;
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->images.current_char, col * 64, row * 64);
	}
	if (data->matrix[row][col] == '1')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->images.img_wall, col * 64, row * 64);
	/*if (data->matrix[row][col] == 'M')
	{
		data->dx = col;
		data->dy = row;
		if (data->flag > 0)
			ft_movenemy(data);
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->images.current_dog, col * 64, row * 64);
	}*/
	if (data->matrix[row][col] == 'C')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->images.img_coll, col * 64, row * 64);
	if (data->matrix[row][col] == 'E')
	{
		data->gx = col;
		if (data->c == 0)
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->images.img_escl, col * 64, (row * 63 - 64));
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->images.current_exit, col * 64, row * 64);
	}
	enemy_list = data->enemy;
	while (enemy_list)
	{
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->images.current_dog, enemy_list->pos.x * 64, enemy_list->pos.y * 64);
		enemy_list = enemy_list->next;
	}
}

void	draw(fdf *data)
{
	int	row;
	int	col;
	int	i;

	row = 0;
	while (row < data->height)
	{
		col = 0;
		while (col < data->width)
		{
			draw2(data, row, col);
			col++;
		}
		row++;
		mlx_string_put(data->mlx_ptr, data->win_ptr, data->width, data->height, 16777215, "MOVES");
		mlx_string_put(data->mlx_ptr, data->win_ptr, data->width * 6, data->height, 16777215, ft_itoa(data->move_count));
	}
}

void	ft_initializer(fdf *data)
{
	data->grass_frames = 0;
	data->dog_frames = 0;
	data->char_frames = 0;
	data->move_count = 0;
	data->images.current_grass = data->images.img_grass_1;
	data->images.current_dog = data->images.img_dog_1;
	data->images.current_char = data->images.img_char_1;
	data->images.current_exit = data->images.img_exit_1;
	data->images.part_an = 0;
	data->i = 1;
	data->en = 0;
}

int	main(int argc, char *argv[])
{
	fdf	data;

	ft_initializer(&data);
	if (argc == 2)
	{
		read_file(argv[1], &data);
		if (ft_checkmap(&data) == 0)
			ft_error("Map");
		ft_printstruct(&data);
		data.mlx_ptr = mlx_init();
		ft_open_images (&data);
		ft_initializer(&data);
		data.win_ptr = mlx_new_window(data.mlx_ptr, data.width * 64, data.height * 64, "FDF");
		draw(&data);
		mlx_key_hook(data.win_ptr, ft_hooks, &data);
		mlx_loop_hook(data.mlx_ptr, ft_updates, &data);
		mlx_loop(data.mlx_ptr);
		ft_freematrix(data.matrix, data.height);
	}
}
