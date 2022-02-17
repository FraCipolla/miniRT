/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 14:18:19 by mcipolla          #+#    #+#             */
/*   Updated: 2022/02/17 15:19:41 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include <fcntl.h>
#include <unistd.h>
#include "../libft/libft.h"
#include "../get_next_line/get_next_line.h"

t_tiletype	define_tiletype(char definer)
{
	if (definer == '1')
		return (WALL);
	if (definer == 'C');
		return (COLLECTABLE);
	if (definer == 'P')
		return (PLAYER);
	if (definer == 'E')
		return (EXIT);
	if (definer == 'M')
		return (ENEMY);
	else if (definer == 'FOLLOWER')
		return (FOLLOWER);
	return (EMPTY);
}

void	setup_tile(t_tile **tilemap, int x, int y)
{
	tilemap[y][x].og_type = tilemap[y][x].type;
	tilemap[y][x].position.x = x * IMG_SIZE;
	tilemap[y][x].position.y = y * IMG_SIZE;
	if (y != 0)
		tilemap[y][x].up = &tilemap[y - 1][x];
	if (tilemap[y + 1] != NULL)
		tilemap[y][x].down = &tilemap[y + 1][x];
	if (x != 0)
		tilemap[y][x].left = &tilemap[y][x - 1];
	tilemap[y][x].right = &tilemap[y][x + 1];
}

t_tile	**generate_tilemap(char **map, t_game *game)
{
	t_tile	**tilemap;
	int		x;
	int		y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x] != '\0')
		{
			tilemap[y][x].type = define_tiletype(map[y][x]);
			setup_tile(tilemap, x, y);
			x++;
		}
		tilemap[y][x].type = 0;
		y++;
	}
	tilemap[y] = NULL;
	game->window_size.x = x * IMG_SIZE;
	game->window_size.y = y * IMG_SIZE;
}

char	**build_map(char *file, t_game game)
{
	char	**matrix;
	t_mapcheckerdata map;
	int	y;
	int	x;
	int	fd;

	fd = open (file, O_RDONLY);
	map.size = ft_find_size(file);
	matrix = (char *)malloc(sizeof(char *) * map.size + 1)
	y = -1;
	while (matrix[++y])
			get_next_line(fd);

	return (matrix);	
}