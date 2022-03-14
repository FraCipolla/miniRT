/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 10:37:42 by mabasset          #+#    #+#             */
/*   Updated: 2022/03/14 23:18:58 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_initializer(t_game *data)
{
	data->grass_frames = 0;
	data->dog_frames = 0;
	data->char_frames = 0;
	data->move_count = 0;
	data->images.cur_grass = data->images.img_grass_1;
	data->images.current_dog = data->images.img_dog_1;
	data->images.current_char = data->images.img_char_1;
	data->images.current_exit = data->images.img_exit_1;
	data->images.part_an = 0;
}

void	ft_error(char *str)
{
	ft_printf("%s Error\n", str);
	exit(1);
}

int	ft_open(char *file_name, int mode)
{
	int	fd;

	fd = open(file_name, mode);
	if (fd < 0)
		ft_error("Open");
	return (fd);
}

void	ft_printstruct(t_game *data)
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
