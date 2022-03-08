/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updates.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 13:15:28 by mcipolla          #+#    #+#             */
/*   Updated: 2022/02/26 12:00:28 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_updates(fdf *data)
{
	int	row;
	int	col;
	int i;

	row = 0;
	data->grass_frames += 1;
	data->dog_frames += 1;
	data->char_frames += 1;
	if (data->grass_frames == 10000 && data->images.current_grass == data->images.img_grass_1)
	{
		data->images.current_grass = data->images.img_grass_2;
		draw(data);
		data->grass_frames = 0;
	}
	if (data->grass_frames == 10000 && data->images.current_grass == data->images.img_grass_2)
	{
		data->images.current_grass = data->images.img_grass_1;
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
	if (data->char_frames == 5000 && data->images.current_char == data->images.img_char_1)
	{
		data->images.current_char = data->images.img_char_2;
		draw(data);
		data->char_frames = 0;
	}
	if (data->char_frames == 5000 && data->images.current_char == data->images.img_char_2)
	{
		data->images.current_char = data->images.img_char_1;
		draw(data);
		data->char_frames = 0;
	}
	
	return (0);
}