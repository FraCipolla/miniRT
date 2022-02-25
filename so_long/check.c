/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabasset <mabasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 02:21:35 by mabasset          #+#    #+#             */
/*   Updated: 2022/02/22 04:03:21 by mabasset         ###   ########.fr       */
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
				data->matrix[row][col] != 'P')
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
				data->p++;
		}
	}
	if (data->c == 0 || (data->e == 0 || data->e > 1)
		|| (data->p == 0 || data->p > 1))
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
