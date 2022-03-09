/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 11:34:41 by mcipolla          #+#    #+#             */
/*   Updated: 2022/03/09 16:52:22 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	move_up(fdf *data)
{
	if (data->matrix[data->y - 1][data->x] != '1' && (data->matrix[data->y - 1][data->x] != 'E' || data->c == 0))
	{
		if (data->matrix[data->y-1][data->x] == 'C')
		{
			data->c--;
			data->images.part_an = 1;
			data->particle_frames = 0;
		}
		data->move_count += 1;
		data->matrix[data->y][data->x] = '0';
		data->matrix[data->y-1][data->x] = 'P';
		return (1);
	}
	return (0);
}

int move_right(fdf *data)
{
	if (data->matrix[data->y][data->x + 1] != '1' && (data->matrix[data->y][data->x + 1] != 'E' || data->c == 0))
	{
		if (data->matrix[data->y][data->x + 1] == 'C')
		{
			data->c--;
			data->images.part_an = 1;
			data->particle_frames = 0;
		}
		data->move_count += 1;
		data->matrix[data->y][data->x] = '0';
		data->matrix[data->y][data->x + 1] = 'P';
		return (1);
	}
	return (0);
}

int	move_left(fdf *data)
{
	if (data->matrix[data->y][data->x - 1] != '1' && (data->matrix[data->y][data->x - 1] != 'E' || data->c == 0))
	{
		if (data->matrix[data->y][data->x - 1] == 'C')
		{
			data->c--;
			data->images.part_an = 1;
			data->particle_frames = 0;
		}
		data->move_count += 1;
		data->matrix[data->y][data->x] = '0';
		data->matrix[data->y][data->x - 1] = 'P';
		return (1);
	}
	return (0);
}

int move_down(fdf *data)
{
	if (data->matrix[data->y + 1][data->x] != '1' && (data->matrix[data->y + 1][data->x] != 'E' || data->c == 0))
	{
		if (data->matrix[data->y + 1][data->x] == 'C')
		{
			data->c--;
			data->images.part_an = 1;
			data->particle_frames = 0;
		}
		data->move_count += 1;
		data->matrix[data->y][data->x] = '0';
		data->matrix[data->y + 1][data->x] = 'P';
		return (1);
	}
	return (0);
}