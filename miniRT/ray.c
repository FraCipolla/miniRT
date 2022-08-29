/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 19:13:42 by mcipolla          #+#    #+#             */
/*   Updated: 2022/08/29 17:37:02 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	**rotation(t_data *data)
{
	double	**matrix;
	double	ori[4];

	ori[1] = data->cam.ori.vec[0];
	ori[2] = data->cam.ori.vec[1];
	ori[3] = data->cam.ori.vec[2];
	matrix = (double **)malloc(sizeof(double *) * 3);
	matrix[0] = malloc(sizeof(double) * 3);
	matrix[1] = malloc(sizeof(double) * 3);
	matrix[2] = malloc(sizeof(double) * 3);
	matrix[0][0] = 1 - 2 * pow(ori[2], 2) - 2 * pow(ori[3], 2);
	matrix[1][0] = 2 * ori[1] * ori[2] + 2 * ori[3];
	matrix[2][0] = 2 * ori[1] * ori[3] - 2 * ori[2];
	matrix[0][1] = 2 * ori[1] * ori[2] - 2 * ori[3];
	matrix[1][1] = 1 - 2 * pow(ori[1], 2) - 2 * pow(ori[3], 2);
	matrix[2][1] = 2 * ori[2] * ori[3] + 2 * ori[1];
	matrix[0][2] = 2 * ori[1] * ori[3] + 2 * ori[2];
	matrix[1][2] = 2 * ori[2] * ori[3] - 2 * ori[1];
	matrix[2][2] = 1 - 2 * pow(ori[1], 2) - 2 * pow(ori[1], 2) - 2 * pow(ori[2], 2);
	// matrix[0][0] = cos(ori[1] * 180) * cos(ori[2] * 180);
	// matrix[1][0] = cos(ori[1] * 180) * sin(ori[2] * 180);
	// matrix[2][0] = -sin(ori[1] * 180);
	// matrix[0][1] = sin(ori[0] * 180) * sin(ori[1] * 180) * cos(ori[2] * 180) - cos(ori[0] * 180) * sin(ori[2] * 180);
	// matrix[1][1] = sin(ori[0] * 180) * sin(ori[1] * 180) * sin(ori[2] * 180) + cos(ori[0] * 180) * cos(ori[2] * 180);;
	// matrix[2][1] = sin(ori[0] * 180) * cos(ori[1] * 180);
	// matrix[0][2] = cos(ori[0] * 180) * sin(ori[1] * 180) * cos(ori[2] * 180) + sin(ori[0] * 180) * sin(ori[2] * 180);
	// matrix[1][2] = cos(ori[0] * 180) * sin(ori[1] * 180) * sin(ori[2] * 180) - sin(ori[0] * 180) * cos(ori[2] * 180);
	// matrix[2][2] = cos(ori[0] * 180) * cos(ori[1] * 180);
	// matrix[0][0] = cos(ori[0] * 180) * cos(ori[1] * 180);
	// matrix[1][0] = sin(ori[0] * 180) * cos(ori[1] * 180);
	// matrix[2][0] = -sin(ori[1] * 180);
	// matrix[0][1] = cos(ori[0] * 180) * sin(ori[1] * 180) * sin(ori[2] * 180) - sin(ori[0] * 180) * cos(ori[2] * 180);
	// matrix[1][1] = sin(ori[0] * 180) * sin(ori[1] * 180) * sin(ori[2] * 180) + cos(ori[0] * 180) * cos(ori[2] * 180);
	// matrix[2][1] = cos(ori[1] * 180) * sin(ori[2] * 180);
	// matrix[0][2] = cos(ori[0] * 180) * sin(ori[1] * 180) * cos(ori[2] * 180) + sin(ori[0] * 180) * sin(ori[2] * 180);
	// matrix[1][2] = sin(ori[0] * 180) * sin(ori[1] * 180) * cos(ori[2] * 180) - cos(ori[0] * 180) * sin(ori[2] * 180);
	// matrix[2][2] = cos(ori[1] * 180) * cos(ori[2] * 180);
	printf("%f %f %f\n", matrix[0][0], matrix[0][1], matrix[0][2]);
	printf("%f %f %f\n", matrix[1][0], matrix[1][1], matrix[1][2]);
	printf("%f %f %f\n", matrix[2][0], matrix[2][1], matrix[2][2]);
	return (matrix);
}

double	*get_direction(int x, int y, t_data *data, double **matrix)
{
	double	*ret;
	double	ori[3];

	ret = malloc(sizeof(double) * 3);
	ret[0] = x / data->width * (data->width / data->height);
	ret[1] = -(y / data->height);
	ret[2] = 1 / tan(data->cam.FOV / 2 * M_PI / 180);
	ret = normalize(ret);
	// ret[0] = ret[0] * matrix[0][0] + ret[1] * matrix[1][0] + ret[2] * matrix[2][0];
	// ret[1] = ret[0] * matrix[0][1] + ret[1] * matrix[1][1] + ret[2] * matrix[2][1];
	// ret[2] = ret[0] * matrix[0][2] + ret[1] * matrix[1][2] + ret[2] * matrix[2][2];
	// ret[0] = ret[0] * matrix[0][0] + ret[1] * matrix[0][1] + ret[2] * matrix[0][2];
	// ret[1] = ret[0] * matrix[1][0] + ret[1] * matrix[1][1] + ret[2] * matrix[1][2];
	// ret[2] = ret[0] * matrix[2][0] + ret[1] * matrix[2][1] + ret[2] * matrix[2][2];
	return ((ret));
}

void	ft_ray(t_data *data)
{
	int		closest_pixel;
	double **matrix = rotation(data);
	
	closest_pixel = create_trgb(0, 255, 255, 255);
	for (int x = -(data->width / 2); x < (data->width / 2); x++)
	{
		for(int y = -(data->height / 2); y < (data->height / 2); y++)
		{
			data->cam.dir.vec = get_direction(x, y, data, matrix);
			closest_pixel = TraceRay(data->cam.pos.vec, data->cam.dir.vec, data);
			my_mlx_pixel_put(data, (data->width / 2) + x, (data->height / 2) + y, closest_pixel);
			}
		}
}