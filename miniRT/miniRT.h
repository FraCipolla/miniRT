#ifndef MINIRT_H
#define MINIRT_H

# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include "mlx.h"
# include "get_next_line/get_next_line.h"

typedef struct s_vec3
{
	double	vec[3]; 
}	t_vec3;

typedef struct s_AmbLight
{
	double		ratio;
	t_vec3		colors;
}	t_AmbLight;

typedef struct s_viewport
{
	t_vec3 dim;
}	t_viewport;

typedef struct s_camera
{
	t_vec3	pos;
	t_vec3	ori;
	int		FOV;
}	t_cam;

typedef struct s_light
{
	t_vec3	pos;
	double	bright;
	t_vec3	colors;
}	t_light;

typedef struct s_sphere
{
	t_vec3			pos;
	double			diam;
	t_vec3			colors;
	struct s_sphere *next;

}	t_sphere;

typedef struct s_plane
{
	t_vec3			pos;
	t_vec3			ori;
	t_vec3			colors;
	struct s_plane	*next;
}	t_plane;

typedef struct s_cylinder
{
	t_vec3				pos;
	t_vec3				ori;
	double				diam;
	double				height;
	t_vec3				colors;
	struct s_cylinder	*next;
}	t_cylind;

typedef struct	s_data {
	void	*mlx;
	void	*mlx_win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	char	**martix;
	t_AmbLight	ambLight;
	t_cam		cam;
	t_light		light;
	t_sphere	*sphere;
	t_plane		*plane;
	t_cylind	*cylinder;
}	t_data;

/* UTILITY */

int		ft_error(char *str);
int		create_trgb(int t, int r, int g, int b);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
char	**ft_split(char const *s, char c);
float	ft_atof(const char *str);
char	*ft_strjoin(char *s1, char *s2);
int		check_arg(t_data *data);
t_vec3	ret_vec(char *args);
int		ft_strcmp(const char *s1, const char *s2);

/* PARSING */
int		parse_buff(char *buff, t_data *data);
int		parse_primitive(char *buff, t_data *data);

#endif