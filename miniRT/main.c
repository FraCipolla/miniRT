/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 17:12:57 by mcipolla          #+#    #+#             */
/*   Updated: 2022/09/01 18:24:16 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	*IntersectRaySphere(t_v3 O, t_v3 D, t_obj *sphere, double *t)
{
	double	a;
	double	b;
	double	c;
	double	ret;
	
	a = dot(D, D);
	b = 2 * dot(sub_vec(O, sphere->pos), D);
	c = dot(sub_vec(O, sphere->pos), sub_vec(O, sphere->pos)) - (sphere->r * sphere->r);
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

double	*find_edges(t_obj *cyl, t_v3 O, t_v3 D, double *t)
{
	double	t2;
	double	max;
	t_v3	point;
	t_v3	len;

	t2 = t[0] < t[1] ? t[0] : t[1];
	max = sqrtf(pow(cyl->h / 2, 2) + pow(cyl->r, 2));
	point = add_vec(O, mult_vec_n(D, t2));
	len = sub_vec(point, cyl->pos);
	if (sqrtf(dot(len, len)) > max)
	{
		t2 = t2 == t[0] ? t[1] : t[0];
		point = add_vec(O, mult_vec_n(D, t2));
		len = sub_vec(point, cyl->pos);
		if (dot(len, len) > max)
			{
				t[0] = INFINITY;
				t[1] = INFINITY;
			}
	}
	return (t);
}

double	*IntersectCylinder(t_v3 O, t_v3 D, t_obj *cyl, double *t)
{
	t_v3	inter;
	double	ret;
	t_v3	R;
	t_v3	c_to_o;
	
	R = cross(D, cyl->ori);
	c_to_o = sub_vec(O, cyl->pos);
	// inter[0] = dot(R, R);
	// inter[1] = 2 * dot(D, cross(c_to_o, cyl->ori));
	// inter[2] = dot(cross(c_to_o, cyl->ori), cross(c_to_o, cyl->ori)) - pow(cyl->diam / 2, 2);
	inter.x = dot(R, R);
	inter.y = 2 * dot(sub_vec(O, cyl->pos), D);
	inter.z = dot(sub_vec(O, cyl->pos), sub_vec(O, cyl->pos)) - (cyl->r * cyl->r);
	ret = sqrtf(inter.x * inter.y - (4 * inter.x * inter.z));
	if (ret < 0)
	{
		t[0] = INFINITY;
		t[1] = INFINITY;
	}
	else
	{
		t[0] = ((-inter.y - (ret)) / (2 * inter.z));
		t[1] = ((-inter.y + (ret)) / (2 * inter.z));
	}
	return (find_edges(cyl, O, D, t));
}

double	*IntersectPlane(t_v3 O, t_v3 D, t_obj *plane, double *t)
{
	if (dot(normalize(plane->ori), D) > 0.0001)
	{
		t[0] = (dot(sub_vec(plane->ori, O), normalize(plane->ori))) / ((dot(normalize(plane->ori), D)));
		if (t[0] <= 0)
			t[0] = INFINITY;
		t[1] = t[0];
	}
	return (t);
}

t_obj	*closest_intersect(t_v3 O, t_v3 D, t_data *data)
{
	t_obj		*closest_obj;
	t_obj		*new;

	new = data->obj;
	closest_obj = NULL;
	data->closest_t = INFINITY;
	data->t[0] = INFINITY;
	data->t[0] = INFINITY;
    while (new)
	{
		if (ft_strcmp(new->id, "sp") == 0)
			data->t = IntersectRaySphere(O, D, new, data->t);
		else if (ft_strcmp(new->id, "pl") == 0)
			data->t = IntersectPlane(O, D, new, data->t);
		else if (ft_strcmp(new->id, "cy") == 0)
			data->t = IntersectCylinder(O, D, new, data->t);	
		if ((data->t[0] >= 1 && data->t[0] < data->closest_t) || (data->t[1] >= 1 && data->t[1] < data->closest_t))
		{
				data->closest_t = data->t[0] < data->t[1] ? data->t[0] : data->t[1];
				closest_obj = new;
		}
		new = new->next;
	}
	return (closest_obj);
}

int	TraceRay(t_v3 O, t_v3 D, t_data *data)
{
    t_obj		*closest_obj;
	double		l;

	closest_obj = closest_intersect(O, D, data);
	if (closest_obj == NULL)
		return (create_trgb(0, 255, 255, 255));
	t_v3	P = add_vec(O, mult_vec_n(D, data->closest_t));
	t_v3	N = sub_vec(P, closest_obj->pos);
	N = normalize(N);
	l = computeLighting(add_vec(O, D), N, data, closest_obj);
	return (create_trgb(0, closest_obj->RGB.x * l, closest_obj->RGB.y * l, closest_obj->RGB.z * l));
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
