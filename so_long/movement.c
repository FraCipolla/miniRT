/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 11:34:41 by mcipolla          #+#    #+#             */
/*   Updated: 2022/03/14 18:19:06 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_movenemy(fdf *data)
{
	t_enemy *enemy_list;

	enemy_list = data->enemy;
	while (enemy_list)
	{
		if (data->matrix[enemy_list->pos.y - 1][enemy_list->pos.x] == '1' || data->matrix[enemy_list->pos.y - 1][enemy_list->pos.x] == 'E' || data->matrix[enemy_list->pos.y - 1][enemy_list->pos.x] == 'C')
				enemy_list->dir = 1;
		else if (data->matrix[enemy_list->pos.y + 1][enemy_list->pos.x] == '1' || data->matrix[enemy_list->pos.y + 1][enemy_list->pos.x] == 'E' || data->matrix[enemy_list->pos.y + 1][enemy_list->pos.x] == 'C')
			enemy_list->dir = -1;
		if (data->matrix[enemy_list->pos.y + enemy_list->dir][enemy_list->pos.x] == 'P')
		{
			mlx_destroy_window(data->mlx_ptr, data->win_ptr);
			exit(0);
		}
		data->matrix[enemy_list->pos.y][enemy_list->pos.x] = '0';
		data->matrix[enemy_list->pos.y + enemy_list->dir][enemy_list->pos.x] = 'M';
		enemy_list->pos.y += enemy_list->dir;
		enemy_list = enemy_list->next;
	}
}

void	move_up(fdf *data)
{
	t_player	*play_list;

	play_list = data->player;
	while (play_list)
	{
		if (data->matrix[play_list->pos.y - 1][play_list->pos.x] != '1' && (data->matrix[play_list->pos.y - 1][play_list->pos.x] != 'E' || data->c == 0))
		{
			if (data->matrix[play_list->pos.y - 1][play_list->pos.x] == 'C')
			{
				data->c--;
				data->images.part_an = 1;
				data->particle_frames = 0;
				data->an_pos = &play_list->pos;
			}
			if (data->matrix[play_list->pos.y - 1][play_list->pos.x] == 'M' || data->matrix[play_list->pos.y - 1][play_list->pos.x] == 'E')
			{
				mlx_destroy_window(data->mlx_ptr, data->win_ptr);
				exit(0);
			}
			data->move_count += 1;
			data->matrix[play_list->pos.y][play_list->pos.x] = '0';
			data->matrix[play_list->pos.y - 1][play_list->pos.x] = 'P';
			play_list->pos.y -= 1;
		}
		play_list = play_list->next;
	}
}

void	move_right(fdf *data)
{
	t_player	*play_list;

	play_list = data->player;
	while (play_list)
	{
		if (data->matrix[play_list->pos.y][play_list->pos.x + 1] != '1' && (data->matrix[play_list->pos.y][play_list->pos.x + 1] != 'E' || data->c == 0))
		{
			if (data->matrix[play_list->pos.y][play_list->pos.x + 1] == 'C')
			{
				data->c--;
				data->images.part_an = 1;
				data->particle_frames = 0;
				data->an_pos = &play_list->pos;
			}
			if (data->matrix[play_list->pos.y][play_list->pos.x + 1] == 'M' || data->matrix[play_list->pos.y][play_list->pos.x + 1] == 'E')
			{
				mlx_destroy_window(data->mlx_ptr, data->win_ptr);
				exit(0);
			}
			data->move_count += 1;
			data->matrix[play_list->pos.y][play_list->pos.x] = '0';
			data->matrix[play_list->pos.y][play_list->pos.x + 1] = 'P';
			play_list->pos.x += 1;
		}
		play_list = play_list->next;
	}
}

void	move_left(fdf *data)
{
	t_player	*play_list;

	play_list =data->player;
	while (play_list)
	{
		if (data->matrix[play_list->pos.y][play_list->pos.x - 1] != '1' && (data->matrix[play_list->pos.y][play_list->pos.x - 1] != 'E' || data->c == 0))
		{
			if (data->matrix[play_list->pos.y][play_list->pos.x - 1] == 'C')
			{
				data->c--;
				data->images.part_an = 1;
				data->particle_frames = 0;
				data->an_pos = &play_list->pos;
			}
			if (data->matrix[play_list->pos.y][play_list->pos.x - 1] == 'M' || data->matrix[play_list->pos.y][play_list->pos.x - 1] == 'E')
			{
				mlx_destroy_window(data->mlx_ptr, data->win_ptr);
				exit(0);
			}
			data->move_count += 1;
			data->matrix[play_list->pos.y][play_list->pos.x] = '0';
			data->matrix[play_list->pos.y][play_list->pos.x - 1] = 'P';
			play_list->pos.x -= 1;
		}
		play_list = play_list->next;
	}
}

void move_down(fdf *data)
{
	t_player	*play_list;

	play_list = data->player;
	while (play_list)
	{
		if (data->matrix[play_list->pos.y + 1][play_list->pos.x] != '1' && (data->matrix[play_list->pos.y + 1][play_list->pos.x] != 'E' || data->c == 0))
		{
			if (data->matrix[play_list->pos.y + 1][play_list->pos.x] == 'C')
			{
				data->c--;
				data->images.part_an = 1;
				data->particle_frames = 0;
				data->an_pos = &play_list->pos;
			}
			if (data->matrix[play_list->pos.y + 1][play_list->pos.x] == 'M' || data->matrix[play_list->pos.y + 1][play_list->pos.x] == 'E')
			{
				mlx_destroy_window(data->mlx_ptr, data->win_ptr);
				exit(0);
			}
			data->move_count += 1;
			data->matrix[play_list->pos.y][play_list->pos.x] = '0';
			data->matrix[play_list->pos.y + 1][play_list->pos.x] = 'P';
			play_list->pos.y += 1;
		}
		play_list = play_list->next;
	}
}
