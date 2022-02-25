/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 11:54:05 by mcipolla          #+#    #+#             */
/*   Updated: 2022/02/25 15:21:20 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_open_images (fdf *data)
{
	data->images.img_wall = mlx_xpm_file_to_image(data->mlx_ptr, "sprites/tree.xpm", &data->img_width, &data->img_height);
	data->images.img_grass_1 = mlx_xpm_file_to_image(data->mlx_ptr, "sprites/grass_idle_1.xpm", &data->img_width, &data->img_height);
	data->images.img_grass_2 = mlx_xpm_file_to_image(data->mlx_ptr, "sprites/grass_idle_2.xpm", &data->img_width, &data->img_height);
	data->images.img_dog_1 = mlx_xpm_file_to_image(data->mlx_ptr, "sprites/dog_idle_1.xpm", &data->img_width, &data->img_height);
	data->images.img_dog_2 = mlx_xpm_file_to_image(data->mlx_ptr, "sprites/dog_idle_2.xpm", &data->img_width, &data->img_height);
	data->images.img_char_1 = mlx_xpm_file_to_image(data->mlx_ptr, "sprites/char_idle_2.xpm", &data->img_width, &data->img_height);
	data->images.img_char_2 = mlx_xpm_file_to_image(data->mlx_ptr, "sprites/char_idle_3.xpm", &data->img_width, &data->img_height);
	data->images.img_coll = mlx_xpm_file_to_image(data->mlx_ptr, "sprites/apple.xpm", &data->img_width, &data->img_height);
}
