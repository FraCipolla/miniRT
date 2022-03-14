/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 11:54:05 by mcipolla          #+#    #+#             */
/*   Updated: 2022/03/14 23:30:49 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_open_images3(t_game *data)
{
	data->images.img_particle6 = mlx_xpm_file_to_image
		(data->mlx_ptr, "sprites/particle_6.xpm",
			&data->img_width, &data->img_height);
	data->images.img_exit_1 = mlx_xpm_file_to_image
		(data->mlx_ptr, "sprites/img_exit_1.xpm",
			&data->img_width, &data->img_height);
	data->images.img_exit_2 = mlx_xpm_file_to_image
		(data->mlx_ptr, "sprites/img_exit_2.xpm",
			&data->img_width, &data->img_height);
	data->images.img_escl = mlx_xpm_file_to_image
		(data->mlx_ptr, "sprites/esclamation.xpm",
			&data->img_width, &data->img_height);
}

void	ft_open_images2(t_game *data)
{
	data->images.img_coll = mlx_xpm_file_to_image
		(data->mlx_ptr, "sprites/apple.xpm",
			&data->img_width, &data->img_height);
	data->images.img_particle1 = mlx_xpm_file_to_image
		(data->mlx_ptr, "sprites/particle_1.xpm",
			&data->img_width, &data->img_height);
	data->images.img_particle2 = mlx_xpm_file_to_image
		(data->mlx_ptr, "sprites/particle_2.xpm",
			&data->img_width, &data->img_height);
	data->images.img_particle3 = mlx_xpm_file_to_image
		(data->mlx_ptr, "sprites/particle_3.xpm",
			&data->img_width, &data->img_height);
	data->images.img_particle4 = mlx_xpm_file_to_image
		(data->mlx_ptr, "sprites/particle_4.xpm",
			&data->img_width, &data->img_height);
	data->images.img_particle5 = mlx_xpm_file_to_image
		(data->mlx_ptr, "sprites/particle_5.xpm",
			&data->img_width, &data->img_height);
}

void	ft_open_images(t_game *data)
{
	data->images.img_wall = mlx_xpm_file_to_image
		(data->mlx_ptr, "sprites/tree.xpm", &data->img_width,
			&data->img_height);
	data->images.img_grass_1 = mlx_xpm_file_to_image
		(data->mlx_ptr, "sprites/grass_idle_1.xpm",
			&data->img_width, &data->img_height);
	data->images.img_grass_2 = mlx_xpm_file_to_image
		(data->mlx_ptr, "sprites/grass_idle_2.xpm",
			&data->img_width, &data->img_height);
	data->images.img_dog_1 = mlx_xpm_file_to_image
		(data->mlx_ptr, "sprites/dog_idle_1.xpm",
			&data->img_width, &data->img_height);
	data->images.img_dog_2 = mlx_xpm_file_to_image
		(data->mlx_ptr, "sprites/dog_idle_2.xpm",
			&data->img_width, &data->img_height);
	data->images.img_char_1 = mlx_xpm_file_to_image
		(data->mlx_ptr, "sprites/char_idle_2.xpm",
			&data->img_width, &data->img_height);
	data->images.img_char_2 = mlx_xpm_file_to_image
		(data->mlx_ptr, "sprites/char_idle_3.xpm",
			&data->img_width, &data->img_height);
	ft_open_images2(data);
	ft_open_images3(data);
}
