/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 17:12:57 by mcipolla          #+#    #+#             */
/*   Updated: 2022/08/07 17:53:53 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// static int	ft_hooks(int keycode, t_data *data)
// {	
// 	if (keycode == 53){
// 		mlx_destroy_window(data->mlx, data->mlx_win);
// 		exit(0);
// 	}
// 	return (0);
// }

void	ft_draw(t_data *data)
{
	double	square[4] = {20, 15, 8, 100};
	double		i;
	double		c;

	c = 0;
	i = 0;
	while (i < 640)
	{
		c = 0;
		while (c < 640)
		{
			if ((c >= 320 + square[0] && c <= 320 + square[0] + square[3]) && (i <= 320 - square[2] && i >= 320 - square[2] - square[3]))
				my_mlx_pixel_put(data, c, i, create_trgb(0, 0, 0, 255));
			else
				my_mlx_pixel_put(data, c, i, create_trgb(0, (i / 640 * 255), (c / 640 * 255), 0));
			c++;
		}
		i++;
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
	// ft_draw(&data);
	// mlx_hook(data.mlx_win, 2, (1 >> 1L), ft_hooks, &data);
	// mlx_put_image_to_window(data.mlx, data.mlx_win, data.img, 0, 0);
	// mlx_loop(data.mlx);
}
