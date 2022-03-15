/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 02:21:35 by mabasset          #+#    #+#             */
/*   Updated: 2022/03/15 00:31:35 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_checkchar(t_game *data)
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

int	ft_checkwalls(t_game *data)
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

int	ft_check_cep(t_game *data)
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
	if (data->c == 0 || data->e == 0 || (data->p == 0))
		return (0);
	return (1);
}

int	ft_checkmap(t_game *data)
{
	if (ft_checkchar(data) == 0)
		return (0);
	else if (ft_checkwalls(data) == 0)
		return (0);
	else if (ft_check_cep(data) == 0)
		return (0);
	return (1);
}
