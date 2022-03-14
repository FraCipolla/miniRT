/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 02:21:35 by mabasset          #+#    #+#             */
/*   Updated: 2022/03/14 18:20:00 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_checkchar(fdf *data)
{
	int	row;
	int	col;

	row = 0;
	while (row < data->height)
	{
		col = 0;
		while (col < data->width)
		{
			if (data->matrix[row][col] != '0' &&
				data->matrix[row][col] != '1' &&
				data->matrix[row][col] != 'C' &&
				data->matrix[row][col] != 'E' &&
				data->matrix[row][col] != 'P' &&
				data->matrix[row][col] != 'M')
				return (0);
			col++;
		}
		row++;
	}
	return (1);
}

int	ft_checkwalls(fdf *data)
{
	int	row;
	int	col;

	row = 0;
	while (row < data->height)
	{
		col = 0;
		while (col < data->width)
		{
			if (data->matrix[row][col] != '1' &&
				((row == 0 || row == data->height - 1) ||
				(col == 0 || col == data->width - 1)))
				return (0);
			col++;
		}
		row++;
	}
	return (1);
}

void	store_enemy(fdf *data, int col, int row)
{
	t_enemy *new;
	t_enemy *enemy_list;

	new = (t_enemy *)malloc(sizeof(t_enemy));
	if (new == NULL)
		return ;
	new->pos.x = col;
	new->pos.y = row;
	new->dir = 1;
	new->next = NULL;
	if (data->enemy == NULL)
		data->enemy = new;
	else
	{
		enemy_list = data->enemy;
		while (enemy_list->next != NULL)
			enemy_list = enemy_list->next;
		enemy_list->next = new;
	}
}

void	store_player(fdf *data, int col, int row)
{
	t_player *new;
	t_player *player_list;

	data->p++;
	data->an_pos = &player_list->pos;
	new = (t_player *)malloc(sizeof(t_player));
	if (new == NULL)
		return ;
	new->pos.x = col;
	new->pos.y = row;
	new->next = NULL;
	if (data->player == NULL)
		data->player = new;
	else
	{
		player_list = data->player;
		while (player_list->next != NULL)
			player_list = player_list->next;
		player_list->next = new;
	}
}

int	ft_check_cep(fdf *data)
{
	int	row;
	int	col;

	data->c = 0;
	data->e = 0;
	data->p = 0;
	row = 0;
	
	while (row++ < data->height - 1)
	{
		col = 0;
		while (col++ < data->width - 1)
		{
			if (data->matrix[row][col] == 'C')
				data->c++;
			else if (data->matrix[row][col] == 'E')
				data->e++;
			else if (data->matrix[row][col] == 'P')
				store_player(data, col, row);
			else if (data->matrix[row][col] == 'M')
				store_enemy(data, col, row);
		}
	}
	if (data->c == 0 || data->e == 0
		|| (data->p == 0))
		return (0);
	return (1);
}

int	ft_checkmap(fdf *data)
{
	if (ft_checkchar(data) == 0)
		return (0);
	else if (ft_checkwalls(data) == 0)
		return (0);
	else if (ft_check_cep(data) == 0)
		return (0);
	return (1);
}
