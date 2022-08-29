/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 17:12:57 by mcipolla          #+#    #+#             */
/*   Updated: 2022/08/29 18:36:29 by mcipolla         ###   ########.fr       */
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

double	*find_edges(t_obj *cyl, double *O, double *D, double *t)
{
	double	t2;
	double	*inters;

	t2 = t[0] < t[1] ? t[0] : t[1];
	inters = add_vec(O, mult_vec_d(D, t2));
	if (dot(dim_vec(inters, cyl->pos.vec), dim_vec(inters, cyl->pos.vec)) > cyl->height)
		return (t);
	t[0] = INFINITY;
	t[1] = INFINITY;
	return (t);
}

double	*IntersectCylinder(double *O, double *D, t_obj *cyl, double *t)
{
	double	*inter;
	double	ret;
	double	*R;
	double	*c_to_o;
	
	inter = malloc(sizeof(double) * 3);
	R = cross(D, cyl->ori.vec);
	c_to_o = dim_vec(O, cyl->pos.vec);
	inter[0] = dot(R, R);
	inter[1] = 2 * dot(D, cross(c_to_o, cyl->ori.vec));
	inter[2] = dot(cross(c_to_o, cyl->ori.vec), cross(c_to_o, cyl->ori.vec)) - pow(cyl->diam / 2, 2);
	ret = sqrtf(inter[1] * inter[1] - (4 * inter[0] * inter[2]));
	if (ret < 0)
	{
		t[0] = INFINITY;
		t[1] = INFINITY;
	}
	else{
		t[0] = ((-inter[1] - (ret)) / (2 * inter[0]));
		t[1] = ((-inter[1] + (ret)) / (2 * inter[0]));
	}
	return (find_edges(cyl, O, D, t));
}

double	*IntersectPlane(double *O, double *D, t_obj *plane, double *t)
{
	t[0] = (dot(dim_vec(plane->ori.vec, O), plane->ori.vec)) / ((dot(plane->ori.vec, D)));
	if (t[0] <= 0)
		t[0] = INFINITY;
	t[1] = t[0];
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
		else if (ft_strcmp(data->obj[i].id, "pl") == 0)
			data->t = IntersectPlane(O, D, &data->obj[i], data->t);
		else if (ft_strcmp(data->obj[i].id, "cy") == 0)
			data->t = IntersectCylinder(O, D, &data->obj[i], data->t);
		if ((data->t[0] >= 1 && data->t[0] < closest) ||
			(data->t[1] >= 1 && data->t[1] < closest))
			{
				closest = data->t[0] < data->t[1] ? data->t[0] : data->t[1];
				closest_obj = &data->obj[i];
			}
	}
	if (closest_obj == NULL)
		return (create_trgb(0, 255, 255, 255));
	D = mult_vec_d(D, closest);
	double *N = normalize(dim_vec(add_vec(O, D), closest_obj->pos.vec));
	l = computeLighting(add_vec(O, D), N, data, closest_obj);
	data->t[0] = 0;
	data->t[1] = 0;
	return (create_trgb(0, closest_obj->RGB[0] * l, closest_obj->RGB[1] * l, closest_obj->RGB[2] * l));
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
