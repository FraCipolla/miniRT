/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 11:12:07 by mcipolla          #+#    #+#             */
/*   Updated: 2022/02/17 14:52:15 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include <fcntl.h>
#include <unistd.h>
#include "../get_next_line/get_next_line.h"

static int	file_linecount(char *file)
{
	int	linecount;
	int	fd;
	int	readcount;
	char	c;

	fd = open(file, O_RDONLY);
	if (!fd)
		return (-1);
	linecount = 1;
	while (TRUE)
	{
		readcount = read(fd, &c, 1);
		if (readcount == 0)
			break ;
		if (readcount < 0)
			return (-1);
		if (c == '\n')
			linecount++;
	}
	close (fd);
	return (linecount);
}

static char	**alloc_columns(char *file)
{
	char	**map;
	int		line_count;

	line_count = file_linecount(file);
	if (line_count <= 0)
		return (NULL);
	map = malloc(sizeof(char *) * line_count + 1);
	if (map == NULL)
		return (NULL);
	return (map);
}

char	**readmap(char *file)
{
	char	**map;
	int		fd;
	int		i;

	map = alloc_columns(file);
	if (map == NULL)
		return (NULL);
	fd = open (file, O_RDONLY);
	i = 0;
	while (get_next_line(fd, &map[i++]));
	map[i] = NULL;
	close (fd);
	return (map);
}