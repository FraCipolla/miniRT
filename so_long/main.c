/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 17:51:17 by mabasset          #+#    #+#             */
/*   Updated: 2022/03/15 04:14:40 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	ft_hooks(int keycode, t_game *data)
{	
	if (keycode == 53)
		end_game(data);
	if (keycode == 13)
		move_up(data);
	else if (keycode == 1)
		move_down(data);
	else if (keycode == 0)
		move_left(data);
	else if (keycode == 2)
		move_right(data);
	ft_printf("MOVES: %d\n", data->move_count);
	draw(data);
	return (0);
}

void	draw2(t_game *data, int row, int col)
{
	t_player	*p_list;

	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->images.cur_grass, col * 64, row * 64);
	if (data->matrix[row][col] == '1')
		mlx_put_image_to_window(data->mlx_ptr,
			data->win_ptr, data->images.img_wall, col * 64, row * 64);
	if (data->matrix[row][col] == 'C')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->images.img_coll, col * 64, row * 64);
	if (data->matrix[row][col] == 'E')
	{
		if (data->c == 0)
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
				data->images.img_escl, col * 64, (row * 63 - 64));
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->images.current_exit, col * 64, row * 64);
	}
	p_list = data->player;
	while (p_list)
	{
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->images.current_char, p_list->pos.x * 64, p_list->pos.y * 64);
		p_list = p_list->next;
	}
}

void	draw(t_game *data)
{
	int			row;
	int			col;
	t_enemy		*enemy_list;
	char		*moves;

	row = -1;
	moves = ft_itoa(data->move_count);
	while (++row < data->height)
	{
		col = -1;
		while (++col < data->width)
			draw2(data, row, col);
		mlx_string_put(data->mlx_ptr, data->win_ptr, data->width,
			data->height, 16777215, moves);
	}
	free(moves);
	enemy_list = data->enemy;
	while (enemy_list)
	{
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->images.current_dog,
			enemy_list->pos.x * 64, enemy_list->pos.y * 64);
		enemy_list = enemy_list->next;
	}
}

int	main(int argc, char *argv[])
{
	t_game	data;

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
		data.win_ptr = mlx_new_window(data.mlx_ptr,
				data.width * 64, data.height * 64, "so_long");
		draw(&data);
		mlx_do_key_autorepeaton(data.mlx_ptr);
		mlx_hook(data.win_ptr, 2, (1 >> 1L), ft_hooks, &data);
		mlx_loop_hook(data.mlx_ptr, ft_updates, &data);
		mlx_loop(data.mlx_ptr);
	}
}
