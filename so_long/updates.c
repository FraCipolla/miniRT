/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updates.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 13:15:28 by mcipolla          #+#    #+#             */
/*   Updated: 2022/03/14 18:35:05 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_particles(fdf *data)
{
	data->particle_frames += 1;
	if (data->particle_frames == 1000)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->images.img_particle1, data->an_pos->x * 64, data->an_pos->y * 64);
	if (data->particle_frames == 2000)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->images.img_particle2, data->an_pos->x * 64, data->an_pos->y * 64);
	if (data->particle_frames == 3000)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->images.img_particle3, data->an_pos->x * 64, data->an_pos->y * 64);
	if (data->particle_frames == 4000)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->images.img_particle4, data->an_pos->x * 64, data->an_pos->y * 64);
	if (data->particle_frames == 50000)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->images.img_particle5, data->an_pos->x * 64, data->an_pos->y * 64);
	if (data->particle_frames == 6000)
	{
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->images.img_particle6, data->an_pos->x * 64, data->an_pos->y * 64);
		data->images.part_an = 0;
	}
}

int	ft_updates(fdf *data)
{
	int	row;
	int	col;
	int i;

	row = 0;
	data->grass_frames += 1;
	data->dog_frames += 1;
	data->char_frames += 1;
	if (data->images.part_an == 1)
		ft_particles(data);
	if (data->grass_frames == 10000 && data->images.current_grass == data->images.img_grass_1)
	{
		data->images.current_grass = data->images.img_grass_2;
		ft_movenemy(data);
		draw(data);
		data->grass_frames = 0;
	}
	if (data->grass_frames == 10000 && data->images.current_grass == data->images.img_grass_2)
	{
		data->images.current_grass = data->images.img_grass_1;
		ft_movenemy(data);
		draw(data);
		data->grass_frames = 0;
	}
	if (data->dog_frames == 1500 && data->images.current_dog == data->images.img_dog_1)
	{
		data->images.current_dog = data->images.img_dog_2;
		draw(data);
		data->dog_frames = 0;
	}
	if (data->dog_frames == 1500 && data->images.current_dog == data->images.img_dog_2)
	{
		data->images.current_dog = data->images.img_dog_1;
		draw(data);
		data->dog_frames = 0;
	}
	if (data->char_frames == 4000 && data->images.current_char == data->images.img_char_1)
	{
		data->images.current_exit = data->images.img_exit_2;
		data->images.current_char = data->images.img_char_2;
		draw(data);
		data->char_frames = 0;
	}
	if (data->char_frames == 4000 && data->images.current_char == data->images.img_char_2)
	{
		data->images.current_exit = data->images.img_exit_1;
		data->images.current_char = data->images.img_char_1;
		draw(data);
		data->char_frames = 0;
	}
	return (0);
}