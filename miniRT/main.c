/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 17:12:57 by mcipolla          #+#    #+#             */
/*   Updated: 2022/08/08 19:15:41 by mcipolla         ###   ########.fr       */
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
		printf("I");
		return (INFINITY);
	}
	printf("N");
	ret = (-b + sqrt(ret)) / (2*a);
    // t2 = (-b - sqrt(discriminant)) / (2*a)
    return (ret);
}

int	TraceRay(double *O, double *D, t_data *data)
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
    return (create_trgb(0, 255, 0, 0));
}

t_vec3	get_direction(int x, int y)
{
	t_vec3	ret;

	ret.vec[0] = x - (640 / 2);
	ret.vec[1] = (640 / 2) - y;
	ret.vec[2] = -640;
	return (ret);
}

void	ft_ray(t_data *data)
{
	int		closest_pixel;

	closest_pixel = create_trgb(0, 0, 0, 0);
	for (int x = 0; x < 640; x++)
	{
		for(int y = 0; y < 640; y++)
		{
			data->cam.dir = get_direction(x, y);
			closest_pixel = TraceRay(data->cam.pos.vec, data->cam.dir.vec, data);
			my_mlx_pixel_put(data, x, y, closest_pixel);
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

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return(ft_error("Error, Invalid Arguments\n"));
	argv = NULL;
	if (argc != 2)
		return(ft_error("Error, Invalid Arguments\n"));
	if (ft_init(&data, fd) != 1)
		exit(0);
	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, 640, 640, "miniRT");
	data.img = mlx_new_image(data.mlx, 640, 640);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length,
								&data.endian);
	ft_ray(&data);
	// ft_draw(&data);
	mlx_hook(data.mlx_win, 2, (1 >> 1L), ft_hooks, &data);
	mlx_put_image_to_window(data.mlx, data.mlx_win, data.img, 0, 0);
	mlx_loop(data.mlx);
}
