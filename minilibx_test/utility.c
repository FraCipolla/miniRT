/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabasset <mabasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 10:37:42 by mabasset          #+#    #+#             */
/*   Updated: 2022/02/18 10:39:07 by mabasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_printstruct(fdf *data)
{
	int	row;
	int	col;

	printf("height: %d\n", data->height);
	printf("width: %d\n", data->width);
	row = 0;
	while (row < data->height)
	{
		col = 0;
		while (col < data->width)
		{
			printf("%3d", data->matrix[row][col]);
			col++;
		}
		printf("\n");
		row++;
	}
}

void	ft_freematrix(int **matrix, int	size)
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
