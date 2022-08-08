/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 17:12:57 by mcipolla          #+#    #+#             */
/*   Updated: 2022/08/08 17:50:48 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3	direction(int x, int y)
{
	t_vec3	ret;
	ret[0] = x - (640 / 2);
	ret[1] = (640 / 2) - y;
	ret[2] = -640;
	return (ret);
}

void	ft_ray(t_data *data)
{
	int		closest_pixel;
	t_vec3	direction;

	closest_pixel = create_trgb(0, 0, 0, 0);
	for (int x = 0; x++; x <= 640)
	{
		for(int y = 0; y++; y <= 640)
		{
			data->cam.dir = direction(x, y);
			closest_pixel = TraceRay(data->cam.pos, data->cam.ori, 1, INFINITY);
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
