/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 18:16:29 by mabasset          #+#    #+#             */
/*   Updated: 2022/03/14 16:47:00 by mcipolla         ###   ########.fr       */
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
	void	*current_dog;
	void	*img_dog_1;
	void	*img_dog_2;
	void	*current_char;
	void	*img_char_1;
	void	*img_char_2;
	void	*img_coll;
	void	*img_exit_1;
	void	*img_exit_2;
	void	*current_exit;
	int		part_an;
	void	*img_particle1;
	void	*img_particle2;
	void	*img_particle3;
	void	*img_particle4;
	void	*img_particle5;
	void	*img_particle6;
	void	*img_escl;
	void	*img_rev_exit_1;
	void	*img_rev_exit_2;
}	t_images;

typedef struct s_vector
{
	int	x;
	int	y;
}	t_vector;

typedef struct s_enemy
{
	t_vector		pos;
	struct s_enemy	*next;
	int				dir;
}	t_enemy;

typedef enum e_tiletype
{
	EMPTY = '0',
	WALL = '1',
	COLLECTABLE = 'C',
	PLAYER = 'P',
	EXIT = 'E',
	ENEMY = 'M',
	FOLLOWER = 'F'
}	t_tiletype;

typedef struct s_player
{
	t_vector			pos;
	struct	s_player	*next;
}	t_player;

typedef	struct
{
	char		**matrix;
	int			height;
	int			width;
	int			img_height;
	int			img_width;
	int			c;
	int			e;
	int			p;
	int			grass_frames;
	int			dog_frames;
	int			char_frames;
	int			move_count;
	int			gx;
	int			particle_frames;
	int			flag;
	int			i;
	int			en;
	t_enemy		*enemy;
	t_player	*player;
	t_vector	an_pos;
	
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
void	draw(fdf *data);
void	move_up(fdf *data);
void 	move_right(fdf *data);
void	move_left(fdf *data);
void 	move_down(fdf *data);
void	ft_movenemy(fdf *data);

#endif
