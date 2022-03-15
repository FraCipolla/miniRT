/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 18:16:29 by mabasset          #+#    #+#             */
/*   Updated: 2022/03/15 00:53:57 by mcipolla         ###   ########.fr       */
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
	void	*cur_grass;
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
	void	*white_panel;
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

typedef struct s_player
{
	t_vector			pos;
	struct s_player		*next;
}	t_player;

typedef struct s_game
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
	int			particle_frames;
	t_enemy		*enemy;
	t_player	*player;
	t_vector	*an_pos;
	void		*mlx_ptr;
	void		*win_ptr;
	t_images	images;
}	t_game;

void	free_list(t_game *data);
void	read_file(char *file_name, t_game *data);
float	ft_max(float a, float b);
float	ft_mod(float i);
void	ft_printstruct(t_game *data);
void	ft_freematrix(t_game *data);
void	ft_color(t_game *data);
void	ft_zoom(float *x1, float *y1, t_game *data);
void	ft_error(char *str);
int		ft_open(char *file_name, int mode);
int		ft_checkmap(t_game *data);
void	ft_open_images(t_game *data);
int		ft_updates(t_game *data);
void	draw(t_game *data);
void	move_up(t_game *data);
void	move_right(t_game *data);
void	move_left(t_game *data);
void	move_down(t_game *data);
void	ft_movenemy(t_game *data);
void	ft_initializer(t_game *data);
void	store_enemy(t_game *data, int col, int row);
void	store_player(t_game *data, int col, int row);
void	end_game(t_game *data);
#endif
