#ifndef MINIRT_H
#define MINIRT_H

# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include "mlx.h"
# include "get_next_line/get_next_line.h"

#define BACKGROUND s_vec3[0, 0, 0]

typedef struct s_vec3
{
	double	*vec;
}	t_vec3;

typedef struct s_AmbLight
{
	double		ratio;
	t_vec3		colors;
}	t_AmbLight;

typedef struct s_viewport
{
	t_vec3 vec;
}	t_viewport;

typedef struct s_camera
{
	t_vec3	pos;
	t_vec3	ori;
	t_vec3	dir;
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
	double	width;
	double	height;
	int		*background;
	t_AmbLight	ambLight;
	t_cam		cam;
	t_light		light;
	t_sphere	*sphere;
	t_plane		*plane;
	t_cylind	*cylinder;
	t_viewport	*viewport;
}	t_data;

/* UTILITY */

int		ft_error(char *str);
char	**ft_split(char const *s, char c);
double	ft_atof(const char *str);
char	*ft_strjoin(char *s1, char *s2);
int		check_arg(t_data *data);
double	*ret_vec(char *args);
int		ft_strcmp(const char *s1, const char *s2);

/* MLX_UTILITY */

int		create_trgb(int t, int r, int g, int b);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		ft_hooks(int keycode, t_data *data);

/* PARSING */
int		parse_buff(char *buff, t_data *data);
int		parse_primitive(char *buff, t_data *data);
double	*get_direction(int x, int y, t_data *data);

/* VEC OPERATIONS */

double	doubleDot(double *v1, double *v2);
double	*dim_vec(double *v1, double *v2);
double	*normalize(double *v1);
double	*mult_vec(double *v1, double *v2);
double	*add_vec(double *v1, double *v2);
double	*div_vec(double *v1, double *v2);
double	get_lenght(double *v1, double *v2);

#endif