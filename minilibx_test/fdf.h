/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 18:16:29 by mabasset          #+#    #+#             */
/*   Updated: 2022/02/18 14:48:38 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>

typedef	struct
{
	int	x;
	int	y;
	int	z;
	int	height;
	int	width;
	int	**matrix;
	int zoom;
	int	color;
	int	shift_x;
	int	shift_y;

	
	void	*mlx_ptr;
	void	*win_ptr;
	void	*bg;
	void	*img;
	void	*wall;
}				fdf;

void	read_file(char *file_name, fdf *data);
float	ft_max(float a, float b);
float	ft_mod(float i);
void	ft_printstruct(fdf *data);
void	ft_freematrix(int **matrix, int	size);
void	ft_color(fdf *data);
void	ft_zoom(float *x1, float *y1, fdf *data);

#endif
