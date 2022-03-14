/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 22:27:41 by mcipolla          #+#    #+#             */
/*   Updated: 2022/03/14 23:23:09 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	end_game(t_game *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	exit(0);
}

void	store_enemy(t_game *data, int col, int row)
{
	t_enemy	*new;
	t_enemy	*enemy_list;

	new = (t_enemy *)malloc(sizeof(t_enemy));
	if (new == NULL)
		return ;
	new->pos.x = col;
	new->pos.y = row;
	new->dir = 1;
	new->next = NULL;
	if (data->enemy == NULL)
		data->enemy = new;
	else
	{
		enemy_list = data->enemy;
		while (enemy_list->next != NULL)
			enemy_list = enemy_list->next;
		enemy_list->next = new;
	}
}

void	store_player(t_game *data, int col, int row)
{
	t_player	*new;
	t_player	*player_list;

	data->p++;
	data->an_pos = &player_list->pos;
	new = (t_player *)malloc(sizeof(t_player));
	if (new == NULL)
		return ;
	new->pos.x = col;
	new->pos.y = row;
	new->next = NULL;
	if (data->player == NULL)
		data->player = new;
	else
	{
		player_list = data->player;
		while (player_list->next != NULL)
			player_list = player_list->next;
		player_list->next = new;
	}
}
