/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 11:07:12 by mabasset          #+#    #+#             */
/*   Updated: 2022/03/20 15:15:56 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	ft_check(int fd, int width)
{
	char	*str;
	int		i;

	str = get_next_line(fd);
	while (str != NULL)
	{
		i = 0;
		while (str[i] != '\n' && str[i] != '\0')
			i++;
		free(str);
		if (i != width)
			ft_error("Map");
		str = get_next_line(fd);
	}
	free(str);
}

int	get_height(char *file_name)
{
	int		height;
	int		fd;
	char	*str;

	fd = ft_open(file_name, O_RDONLY);
	str = get_next_line(fd);
	height = 0;
	while (str != NULL)
	{
		height++;
		free(str);
		str = get_next_line(fd);
	}
	free(str);
	close(fd);
	if (height < 3)
		ft_error("Map");
	return (height);
}

int	get_width(char *file_name)
{
	char	*str;
	int		width;
	int		i;
	int		fd;

	fd = ft_open(file_name, O_RDONLY);
	str = get_next_line(fd);
	if (str == NULL)
		ft_error("Map");
	width = 0;
	while (str[width] != '\n' && str[width] != '\0')
		width++;
	free(str);
	ft_check(fd, width);
	close(fd);
	if (width < 3)
		ft_error("Map");
	return (width);
}

static void	ft_strcpy(char *matrix, const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
	{
		matrix[i] = str[i];
		i++;
	}
	matrix[i] = '\0';
}

void	read_file(char *file_name, t_game *data)
{
	int		row;
	int		fd;
	char	*str;

	data->height = get_height(file_name);
	data->width = get_width(file_name);
	data->matrix = (char **) malloc (sizeof(char *) * data->height + 1);
	data->matrix[data->height] = NULL;
	if (data->matrix == NULL)
		ft_error("Malloc");
	fd = ft_open(file_name, O_RDONLY);
	row = 0;
	while (row < data->height)
	{
		data->matrix[row] = (char *) malloc (sizeof(char) * data->width + 1);
		if (data->matrix[row] == NULL)
			ft_error("Malloc");
		str = get_next_line(fd);
		ft_strcpy(data->matrix[row], str);
		free(str);
		row++;
	}
	close(fd);
}
