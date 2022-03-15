/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 11:34:41 by mcipolla          #+#    #+#             */
/*   Updated: 2022/03/15 03:58:25 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_movenemy(t_game *d)
{
	t_enemy	*en;

	en = d->enemy;
	while (en)
	{
		if (d->matrix[en->pos.y - 1][en->pos.x] == '1'
		|| d->matrix[en->pos.y - 1][en->pos.x] == 'E'
		|| d->matrix[en->pos.y - 1][en->pos.x] == 'C')
				en->dir = 1;
		else if (d->matrix[en->pos.y + 1][en->pos.x] == '1'
		|| d->matrix[en->pos.y + 1][en->pos.x] == 'E'
		|| d->matrix[en->pos.y + 1][en->pos.x] == 'C')
			en->dir = -1;
		if (d->matrix[en->pos.y + en->dir][en->pos.x] == 'P')
		{
			mlx_destroy_window(d->mlx_ptr, d->win_ptr);
			exit(0);
		}
		d->matrix[en->pos.y][en->pos.x] = '0';
		d->matrix[en->pos.y + en->dir][en->pos.x] = 'M';
		en->pos.y += en->dir;
		en = en->next;
	}
}

void	move_up(t_game *d)
{
	t_player	*pl;

	pl = d->player;
	while (pl)
	{
		if (d->matrix[pl->pos.y - 1][pl->pos.x] != '1'
		&& (d->matrix[pl->pos.y - 1][pl->pos.x] != 'E' || d->c == 0))
		{
			if (d->matrix[pl->pos.y - 1][pl->pos.x] == 'C')
			{
				d->c--;
				d->images.part_an = 1;
				d->particle_frames = 0;
				d->an_pos = &pl->pos;
			}
			if (d->matrix[pl->pos.y - 1][pl->pos.x] == 'M'
			|| d->matrix[pl->pos.y - 1][pl->pos.x] == 'E')
				end_game(d);
			d->move_count += 1;
			d->matrix[pl->pos.y][pl->pos.x] = '0';
			d->matrix[pl->pos.y - 1][pl->pos.x] = 'P';
			pl->pos.y -= 1;
		}
		pl = pl->next;
	}
}

void	move_right(t_game *d)
{
	t_player	*pl;

	pl = d->player;
	while (pl)
	{
		if (d->matrix[pl->pos.y][pl->pos.x + 1] != '1'
		&& (d->matrix[pl->pos.y][pl->pos.x + 1] != 'E' || d->c == 0))
		{
			if (d->matrix[pl->pos.y][pl->pos.x + 1] == 'C')
			{
				d->c--;
				d->images.part_an = 1;
				d->particle_frames = 0;
				d->an_pos = &pl->pos;
			}
			if (d->matrix[pl->pos.y][pl->pos.x + 1] == 'M'
			|| d->matrix[pl->pos.y][pl->pos.x + 1] == 'E')
				end_game(d);
			d->move_count += 1;
			d->matrix[pl->pos.y][pl->pos.x] = '0';
			d->matrix[pl->pos.y][pl->pos.x + 1] = 'P';
			pl->pos.x += 1;
		}
		pl = pl->next;
	}
}

void	move_left(t_game *d)
{
	t_player	*pl;

	pl = d->player;
	while (pl)
	{
		if (d->matrix[pl->pos.y][pl->pos.x - 1] != '1'
		&& (d->matrix[pl->pos.y][pl->pos.x - 1] != 'E' || d->c == 0))
		{
			if (d->matrix[pl->pos.y][pl->pos.x - 1] == 'C')
			{
				d->c--;
				d->images.part_an = 1;
				d->particle_frames = 0;
				d->an_pos = &pl->pos;
			}
			if (d->matrix[pl->pos.y][pl->pos.x - 1] == 'M'
			|| d->matrix[pl->pos.y][pl->pos.x - 1] == 'E')
				end_game(d);
			d->move_count += 1;
			d->matrix[pl->pos.y][pl->pos.x] = '0';
			d->matrix[pl->pos.y][pl->pos.x - 1] = 'P';
			pl->pos.x -= 1;
		}
		pl = pl->next;
	}
}

void	move_down(t_game *d)
{
	t_player	*pl;

	pl = d->player;
	while (pl)
	{
		if (d->matrix[pl->pos.y + 1][pl->pos.x] != '1'
		&& (d->matrix[pl->pos.y + 1][pl->pos.x] != 'E' || d->c == 0))
		{
			if (d->matrix[pl->pos.y + 1][pl->pos.x] == 'C')
			{
				d->c--;
				d->images.part_an = 1;
				d->particle_frames = 0;
				d->an_pos = &pl->pos;
			}
			if (d->matrix[pl->pos.y + 1][pl->pos.x] == 'M'
			|| d->matrix[pl->pos.y + 1][pl->pos.x] == 'E')
				end_game(d);
			d->move_count += 1;
			d->matrix[pl->pos.y][pl->pos.x] = '0';
			d->matrix[pl->pos.y + 1][pl->pos.x] = 'P';
			pl->pos.y += 1;
		}
		pl = pl->next;
	}
}
