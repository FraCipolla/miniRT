/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updates.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 13:15:28 by mcipolla          #+#    #+#             */
/*   Updated: 2022/02/25 13:19:43 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_updates(fdf *data)
{
	data->frames += 1;

	if (data->frames % 6 == 0 && data->images.current_grass == data->images.img_grass_1)
		data->images.current_grass = data->images.img_grass_2;
	return (0);
}