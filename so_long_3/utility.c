/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabasset <mabasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 10:37:42 by mabasset          #+#    #+#             */
/*   Updated: 2022/02/21 22:19:27 by mabasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_error(char *str)
{
	ft_printf("%s Error\n", str);
	exit(1);
}

int		ft_open(char *file_name, int mode)
{
	int	fd;

	fd = open(file_name, mode);
	if (fd < 0)
		ft_error("Open");
	return (fd);
}

void	ft_printstruct(fdf *data)
{
	int	row;

	ft_printf("height: %d\n", data->height);
	ft_printf("width: %d\n", data->width);
	row = 0;
	while (data->matrix[row] != NULL)
	{
		ft_printf("%s\n", data->matrix[row]);
		row++;
	}
}

void	ft_freematrix(char **matrix, int size)
{
	int	row;

	row = 0;
	while (row < size)
	{
		free(matrix[row]);
		row++;
	}
	free(matrix);
}
