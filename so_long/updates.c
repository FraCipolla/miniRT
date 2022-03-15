/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updates.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 13:15:28 by mcipolla          #+#    #+#             */
/*   Updated: 2022/03/15 15:39:26 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_particles(t_game *data)
{
	if (data->particle_frames == 1000)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->images.img_particle1, data->an_pos->x * 64,
			data->an_pos->y * 64);
	if (data->particle_frames == 2000)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->images.img_particle2, data->an_pos->x * 64,
			data->an_pos->y * 64);
	if (data->particle_frames == 3000)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->images.img_particle3, data->an_pos->x * 64,
			data->an_pos->y * 64);
	if (data->particle_frames == 4000)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->images.img_particle4, data->an_pos->x * 64,
			data->an_pos->y * 64);
	if (data->particle_frames == 50000)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->images.img_particle5, data->an_pos->x * 64,
			data->an_pos->y * 64);
	if (data->particle_frames == 6000)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->images.img_particle6,
			data->an_pos->x * 64, data->an_pos->y * 64);
}

void	ft_grass_ani(t_game *data)
{
	if (data->images.cur_grass == data->images.img_grass_1)
	{
		data->images.cur_grass = data->images.img_grass_2;
		ft_movenemy(data);
		draw(data);
		data->grass_frames = 0;
	}
	else
	{
		data->images.cur_grass = data->images.img_grass_1;
		ft_movenemy(data);
		draw(data);
		data->grass_frames = 0;
	}
}

void	ft_dog_ani(t_game *data)
{
	if (data->images.current_dog == data->images.img_dog_1)
	{
		data->images.current_dog = data->images.img_dog_2;
		draw(data);
		data->dog_frames = 0;
	}
	else
	{
		data->images.current_dog = data->images.img_dog_1;
		draw(data);
		data->dog_frames = 0;
	}
}

void	ft_char_ani(t_game *data)
{
	if (data->images.current_char == data->images.img_char_1)
	{
		data->images.current_exit = data->images.img_exit_2;
		data->images.current_char = data->images.img_char_2;
		draw(data);
		data->char_frames = 0;
	}
	else
	{
		data->images.current_exit = data->images.img_exit_1;
		data->images.current_char = data->images.img_char_1;
		draw(data);
		data->char_frames = 0;
	}
}

int	ft_updates(t_game *data)
{
	int	row;
	int	col;
	int	i;

	row = 0;
	data->grass_frames += 1;
	data->dog_frames += 1;
	data->char_frames += 1;
	if (data->particle_frames == 6000)
		data->images.part_an = 0;
	if (data->images.part_an == 1)
	{
		data->particle_frames += 1;
		ft_particles(data);
	}
	if (data->grass_frames == 10000)
		ft_grass_ani(data);
	if (data->dog_frames == 1500)
		ft_dog_ani(data);
	if (data->char_frames == 4000)
		ft_char_ani(data);
	return (0);
}
