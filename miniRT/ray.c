/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 19:13:42 by mcipolla          #+#    #+#             */
/*   Updated: 2022/09/01 20:09:17 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_v3	mult_quat(t_v3 v, t_v3 rot)
{
	t_v3	ret;
	// rot.x = rot.x * 360;
	// rot.y = rot.y * 360;
	// rot.z = rot.z * 360;
	ret.x = v.x * 1 + v.x * rot.x + v.x * rot.y + v.x * rot.z;
	ret.y = v.y * 1 + v.y * rot.x + v.y * rot.y + v.y * rot.z;
	ret.z =	v.z * 1 + v.z * rot.x + v.z * rot.y + v.z * rot.z;
	ret.x = v.x * 1 + v.x * -rot.x + v.x * -rot.y + v.x * -rot.z;
	ret.y = v.y * 1 + v.y * -rot.y + v.y * -rot.y + v.y * -rot.z;
	ret.z = v.z * 1 + v.z * -rot.z + v.z * -rot.y + v.z * -rot.z;
	return (ret);
}

t_v3	get_direction(int x, int y, t_data *data)
{
	t_v3	ret;
	double	ori[3];

	ret.x = x / data->width * (data->width / data->height);
	ret.y = -(y / data->height);
	ret.z = 1 / tan(data->cam.FOV / 2 * M_PI / 180);
	// ret = normalize(ret);
	return (ret);
}

void	ft_ray(t_data *data)
{
	int		closest_pixel;
	
	closest_pixel = create_trgb(0, 255, 255, 255);
	for (int x = -(data->width / 2); x < (data->width / 2); x++)
	{
		for(int y = -(data->height / 2); y < (data->height / 2); y++)
		{
			data->cam.dir = get_direction(x, y, data);
			closest_pixel = TraceRay(data->cam.pos, data->cam.dir, data);
			my_mlx_pixel_put(data, (data->width / 2) + x, (data->height / 2) + y, closest_pixel);
			}
		}
}