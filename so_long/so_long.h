/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 18:16:29 by mabasset          #+#    #+#             */
/*   Updated: 2022/02/25 13:16:09 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft/libft.h"
# include "mlx.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>

typedef struct s_images
{
	void	*img_wall;
	void	*current_grass;
	void	*img_grass_1;
	void	*img_grass_2;
	void	*img_dog_1;
	void	*img_dog_2;
}	t_images;

typedef	struct
{
	char	**matrix;
	int		height;
	int		width;
	int		img_height;
	int		img_width;
	int		c;
	int		e;
	int		p;
	int		frames;
	
	void	*mlx_ptr;
	void	*win_ptr;
	t_images	images;
}				fdf;

void	read_file(char *file_name, fdf *data);
float	ft_max(float a, float b);
float	ft_mod(float i);
void	ft_printstruct(fdf *data);
void	ft_freematrix(char **matrix, int size);
void	ft_color(fdf *data);
void	ft_zoom(float *x1, float *y1, fdf *data);
void	ft_error(char *str);
int		ft_open(char *file_name, int mode);
int		ft_checkmap(fdf *data);
void	ft_open_images(fdf *data);
int		ft_updates(fdf *data);

#endif
