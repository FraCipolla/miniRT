/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 17:12:57 by mcipolla          #+#    #+#             */
/*   Updated: 2022/08/10 18:49:44 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	IntersectRaySphere(double *O, double *D, t_sphere *sphere)
{
	double	a;
	double	b;
	double	c;
	double	ret;
	
	a = doubleDot(D, D);
	b = 2 * doubleDot(dim_vec(O, sphere->pos.vec), D);
	c = doubleDot(dim_vec(O, sphere->pos.vec), dim_vec(O, sphere->pos.vec)) - ((sphere->diam / 2) * (sphere->diam / 2));

	ret = b*b - 4*a*c;
	if (ret < 0)
	{
		return (INFINITY);
	}
	ret = ((-b - sqrt(ret)) / (2*a)) < ((-b + sqrt(ret)) / (2*a)) ? ((-b - sqrt(ret)) / (2*a)) : ((-b + sqrt(ret)) / (2*a));
    return (ret);
}

double	computeLighting(double *P, double *N, t_data *data)
{
	double	i;
	double	*L;
	double dot;

	i = 0.0;
	i += data->ambLight.ratio;
	// printf("I: %f\n", i);
	L = dim_vec(data->light.pos.vec, P);
	dot = doubleDot(N, L);
	if (dot > 0)
		i +=((data->ambLight.ratio * dot) / (doubleDot(normalize(N), normalize(L))));
	return (i);
}

double	TraceRay(double *O, double *D, t_data *data)
{
	double	t1;
	double 	closest = INFINITY;
    t_sphere	*closest_sphere = NULL;
	t_sphere	*new;

	new = data->sphere;
    while (new)
	{
		t1 = IntersectRaySphere(O, D, new);
		if (t1 < closest)
		{
			closest = t1;
			closest_sphere = new;
		}
		new = new->next;
	}
    if (closest_sphere == NULL)
		return (create_trgb(0, 0, 0, 0));
	D[0] = D[0] * closest;
	D[1] = D[1] * closest;
	D[2] = D[2] * closest;
	double *P = add_vec(O, D);
	double *N = dim_vec(P, closest_sphere->pos.vec);
	N = normalize(N);
    return (create_trgb(255 * computeLighting(P, N, data), closest_sphere->colors.vec[0], closest_sphere->colors.vec[1], closest_sphere->colors.vec[2]));
}

double	*get_direction(int x, int y, t_data *data)
{
	double	*ret;

	ret = malloc(sizeof(double) * 3);
	ret[0] = x * (1 / data->width) * (data->width / data->height);
	// ret[0] = ((2 * ((x + 0.5) / data->width) - 1) * tan(data->cam.FOV / 2 * M_PI / 180) * (data->width / data->height));
	ret[1] = -(y * (1 / data->height));
	// ret[1] = (1 - 2 * ((y + 0.5) / data->height)) * tan(data->cam.FOV / 2 * M_PI / 180);
	ret[2] = 1;
	return (normalize(ret));
}

void	ft_ray(t_data *data)
{
	double		closest_pixel;

	closest_pixel = create_trgb(0, 0, 0, 0);
	for (int x = -(data->width / 2); x < (data->width / 2); x++)
	{
		for(int y = -(data->height / 2); y < (data->height / 2); y++)
		{
			data->cam.dir.vec = get_direction(x, y, data);
			closest_pixel = TraceRay((data->cam.pos.vec), data->cam.dir.vec, data);
			my_mlx_pixel_put(data, (data->width / 2) + x, (data->height / 2) + y, closest_pixel);
			}
		}
}

int	ft_init(t_data *data, int fd)
{
	char	*buff;
	char	*to_matrix;
	int i;

	while (fd > 0)
	{
		buff = get_next_line(fd);
		if (buff == NULL)
			break ;
		to_matrix = ft_strjoin(to_matrix, buff);
		free (buff);
	}
	data->martix = ft_split(to_matrix, '\n');
	if (check_arg(data) == 0)
		ft_error("Invalid Arguments\n");
	i = -1;
	while (data->martix[++i])
	{
		parse_buff(data->martix[i], data);
		printf("%s\n", data->martix[i]);
	}
	return (1);
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
	argv = NULL;
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
	mlx_put_image_to_window(data.mlx, data.mlx_win, data.img, 0, 0);
	mlx_loop(data.mlx);
}
