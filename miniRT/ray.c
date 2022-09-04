/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 19:13:42 by mcipolla          #+#    #+#             */
/*   Updated: 2022/09/04 19:17:52 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_ray	get_direction(int x, int y, t_data *data)
{
	t_v3	ret;
	t_ray	ray;

	ret.x = (x * (1 / data->width)) * (data->width / data->height) * tan(data->cam.FOV / 2 * M_PI / 180);
	ret.y = (y * (1 / data->height)) * tan(data->cam.FOV / 2 * M_PI / 180);
	ret.z = 1;
	ray.origin = mat4_get(data->cam.world, 3);
	ray.dir = normalize(mat4_mult_dir(data->cam.world, ret));
	ray.max = INFINITY;
	return (ray);
}

void	ft_ray(t_data *data)
{
	int		closest_pixel;
	t_v3	origin;
	
	closest_pixel = create_trgb(0, 255, 255, 255);
	for (int x = -(data->width / 2); x < (data->width / 2); x++)
	{
		for(int y = (data->height / 2); y > -(data->height / 2); y--)
		{
			data->ray = get_direction(x, y, data);
			// data->cam.dir = look_at(data->cam.dir, data->cam.ori);
			// printf("%f %f %f\n", data->cam.dir.x, data->cam.dir.y, data->cam.dir.z);
			closest_pixel = TraceRay(data->ray.origin, data->ray.dir, data);
			my_mlx_pixel_put(data, (data->width / 2) + x, (data->height / 2) - y, closest_pixel);
			}
		}
}