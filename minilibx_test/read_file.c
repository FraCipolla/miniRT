/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 11:07:12 by mabasset          #+#    #+#             */
/*   Updated: 2022/02/19 12:17:18 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_height(char *file_name)
{
	int	height;
	int fd;
	char *str;

	fd = open(file_name, O_RDONLY);
	str = get_next_line(fd);
	height = 0;
	while(str != NULL)
	{
		height++;
		free(str);
		str = get_next_line(fd);
	}
	free(str);
	close(fd);
	return (height);
}

int	get_width(char *file_name)
{
	char	*str;
	int		width;
	int		i;
	int		fd;

	fd = open(file_name, O_RDONLY);
	str = get_next_line(fd);
	width = 0;
	i = 0;
	while (str[i] != '\0')
	{
		while(str[i] == ' ')
			i++;
		width += 1;
		while(str[i] != ' ' && str[i] != '\0')
			i++;
	}
	free(str);
	close(fd);
	return (width);
}

static void	ft_putstr(int *matrix, const char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[j] != '\0')
	{
		while (line[j] == ' ')
			j++;
		matrix[i] = ft_atoi(line + j);
		i++;
		while (line[j] != ' ' && line[j] != '\0')
			j++;
	}
}

void	read_file(char *file_name, fdf *data)
{
	int		row;
	int		fd;
	char	*str; 

	data->height = get_height(file_name);
	data->width = get_width(file_name);
	data->matrix = malloc (sizeof(int *) * data->height);
	if (data->matrix == NULL)
		exit(1);
	fd = open(file_name, O_RDONLY);
	row = 0;
	while(row < data->height)
	{
		data->matrix[row] = malloc (sizeof(int) * data->width);
		if (data->matrix[row] == NULL)
			exit(1);
		str = get_next_line(fd);
		ft_putstr(data->matrix[row], str);
		free(str);
		row++;
	}
	close(fd);
}
