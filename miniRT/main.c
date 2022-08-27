/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 17:12:57 by mcipolla          #+#    #+#             */
/*   Updated: 2022/08/27 18:10:28 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	*IntersectRaySphere(double *O, double *D, t_obj *sphere, double *t)
{
	double	a;
	double	b;
	double	c;
	double	ret;
	
	a = dot(D, D);
	b = 2 * dot(dim_vec(O, sphere->pos.vec), D);
	c = dot(dim_vec(O, sphere->pos.vec), dim_vec(O, sphere->pos.vec)) - (sphere->diam / 2 * sphere->diam / 2);
	ret = sqrtf(b * b - (4 * a * c));
	if (ret < 0)
	{
		t[0] = INFINITY;
		t[1] = INFINITY;
	}
	else{
		t[0] = ((-b - (ret)) / (2 * a));
		t[1] = ((-b + (ret)) / (2 * a));
	}
    return (t);
}

int	TraceRay(double *O, double *D, t_data *data)
{
	double 		closest = INFINITY;
    t_obj		*closest_obj = NULL;
	double		l;
	int			i;
	
	i = -1;
    while (++i < data->obj_size)
	{
		if (ft_strcmp(data->obj[i].id, "sp") == 0)
			data->t = IntersectRaySphere(O, D, &data->obj[i], data->t);
		if ((data->t[0] >= 1 && data->t[0] < closest) ||
			(data->t[1] >= 1 && data->t[1] < closest))
			{
				closest = data->t[0] < data->t[1] ? data->t[0] : data->t[1];
				closest_obj = &data->obj[i];
			}
	}
	if (closest_obj == NULL){
		return (create_trgb(0, 255, 255, 255));
	}
	D = mult_vec_d(D, closest);
	double *N = normalize(dim_vec(add_vec(O, D), closest_obj->pos.vec));
	l = computeLighting(add_vec(O, D), N, data, closest_obj);
	return (create_trgb(0, closest_obj->RGB[0] * l, closest_obj->RGB[1] * l, closest_obj->RGB[2] * l));
}

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
	// printf("%f %f %f\n", matrix[0][0], matrix[0][1], matrix[0][2]);
	// printf("%f %f %f\n", matrix[1][0], matrix[1][1], matrix[1][2]);
	// printf("%f %f %f\n", matrix[2][0], matrix[2][1], matrix[2][2]);
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
	// ret[0] = ret[0] * matrix[0][0] + ret[1] * matrix[0][1] + ret[2] * matrix[0][2];
	// ret[1] = ret[0] * matrix[1][0] + ret[1] * matrix[1][1] + ret[2] * matrix[1][2];
	// ret[2] = ret[0] * matrix[2][0] + ret[1] * matrix[2][1] + ret[2] * matrix[2][2];
	// printf("%f %f %f\n", ret[0], ret[1], ret[2]);
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

int	main(int argc, char *argv[])
{
	t_data	data;
	int		fd;

	data.width = 1080;
	data.height = 720;
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return(ft_error("Error, Invalid Arguments\n"));
	if (argc != 2)
		return(ft_error("Error, Invalid Arguments\n"));
	if (ft_init(&data, fd) != 1)
		exit(0);
	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, data.width, data.height, "miniRT");
	data.img = mlx_new_image(data.mlx, data.width, data.height);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length,
								&data.endian);
	ft_ray(&data);
	mlx_hook(data.mlx_win, 2, (1 >> 1L), ft_hooks, &data);
	// mlx_hook(data.mlx_win, 17, 0, ft_error, &data);
	mlx_put_image_to_window(data.mlx, data.mlx_win, data.img, 0, 0);
	mlx_loop(data.mlx);
}
