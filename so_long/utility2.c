/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 22:27:41 by mcipolla          #+#    #+#             */
/*   Updated: 2022/03/15 04:00:16 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	end_game(t_game *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	ft_freematrix(data);
	exit(0);
}

t_enemy	*last_enemy(t_enemy *enemy)
{
	if (!enemy)
		return (NULL);
	while (enemy->next)
		enemy = enemy->next;
	return (enemy);
}

void	store_enemy(t_game *data, int col, int row)
{
	t_enemy	*new;

	new = malloc(sizeof(t_enemy));
	new->pos.x = col;
	new->pos.y = row;
	new->dir = 1;
	new->next = NULL;
	if (new == NULL)
		return ;
	if (data->enemy == NULL)
		data->enemy = new;
	else
		last_enemy(data->enemy)->next = new;
}

t_player	*last_player(t_player *player)
{
	if (!player)
		return (NULL);
	while (player->next)
		player = player->next;
	return (player);
}

void	store_player(t_game *data, int col, int row)
{
	t_player	*new;

	data->p++;
	data->an_pos = &data->player->pos;
	new = malloc(sizeof(t_player));
	new->pos.x = col;
	new->pos.y = row;
	new->next = NULL;
	if (new == NULL)
		return ;
	if (data->player == NULL)
		data->player = new;
	else
		last_player(data->player)->next = new;
}
