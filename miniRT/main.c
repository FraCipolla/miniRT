/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 17:12:57 by mcipolla          #+#    #+#             */
/*   Updated: 2022/08/30 16:02:50 by mcipolla         ###   ########.fr       */
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
	b = 2 * dot(sub_vec(O, sphere->pos.vec), D);
	c = dot(sub_vec(O, sphere->pos.vec), sub_vec(O, sphere->pos.vec)) - (sphere->diam / 2 * sphere->diam / 2);
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
	double	max;
	double	*point;
	double	*len;

	t2 = t[0] < t[1] ? t[0] : t[1];
	max = sqrtf(pow(cyl->height / 2, 2) + pow(cyl->diam / 2, 2));
	point = add_vec(O, mult_vec_n(D, t2));
	len = sub_vec(point, cyl->pos.vec);
	if (sqrtf(dot(len, len)) > max)
	{
		t2 = t2 == t[0] ? t[1] : t[0];
		point = add_vec(O, mult_vec_n(D, t2));
		len = sub_vec(point, cyl->pos.vec);
		if (dot(len, len) > max)
			{
				t[0] = INFINITY;
				t[1] = INFINITY;
			}
	}
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
	c_to_o = sub_vec(O, cyl->pos.vec);
	// inter[0] = dot(R, R);
	// inter[1] = 2 * dot(D, cross(c_to_o, cyl->ori.vec));
	// inter[2] = dot(cross(c_to_o, cyl->ori.vec), cross(c_to_o, cyl->ori.vec)) - pow(cyl->diam / 2, 2);
	inter[0] = dot(R, R);
	inter[1] = 2 * dot(sub_vec(O, cyl->pos.vec), D);
	inter[2] = dot(sub_vec(O, cyl->pos.vec), sub_vec(O, cyl->pos.vec)) - (cyl->diam / 2 * cyl->diam / 2);
	ret = sqrtf(inter[1] * inter[1] - (4 * inter[0] * inter[2]));
	if (ret < 0)
	{
		t[0] = INFINITY;
		t[1] = INFINITY;
	}
	else
	{
		t[0] = ((-inter[1] - (ret)) / (2 * inter[0]));
		t[1] = ((-inter[1] + (ret)) / (2 * inter[0]));
	}
	return (find_edges(cyl, O, D, t));
}

double	*IntersectPlane(double *O, double *D, t_obj *plane, double *t)
{
	if (dot(normalize(plane->ori.vec), D) > 0.0001)
	{
		t[0] = (dot(sub_vec(plane->ori.vec, O), normalize(plane->ori.vec))) / ((dot(normalize(plane->ori.vec), D)));
		if (t[0] <= 0)
			t[0] = INFINITY;
		t[1] = t[0];
	}
	return (t);
}

t_obj	*closest_intersect(double *O, double *D, t_data *data)
{
	double 		closest = INFINITY;
	t_obj		*closest_obj = NULL;
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
		if ((data->t[0] >= 1 && data->t[0] < closest) || (data->t[1] >= 1 && data->t[1] < closest))
		{
				data->closest_t = data->t[0] < data->t[1] ? data->t[0] : data->t[1];
				closest_obj = &data->obj[i];
		}
	}
	return (closest_obj);
}

int	TraceRay(double *O, double *D, t_data *data)
{
    t_obj		*closest_obj = NULL;
	double		l;
	
	closest_obj = closest_intersect(O, D, data);
	if (closest_obj == NULL)
		return (create_trgb(0, 255, 255, 255));
	double *P = add_vec(O, mult_vec_n(D, data->closest_t));
	double *N = sub_vec(P, closest_obj->pos.vec);
	N = normalize(N);
	l = computeLighting(add_vec(O, D), N, data, closest_obj);
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
