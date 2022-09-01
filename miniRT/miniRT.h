#ifndef MINIRT_H
#define MINIRT_H

# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include "mlx.h"
# include "get_next_line/get_next_line.h"

#define BG int[0, 0, 0]

typedef struct s_v3
{
	double	x;
	double	y;
	double	z;
}	t_v3;

typedef struct s_light
{
	char			t;
	double			ratio;
	t_v3			pos;
	t_v3			RGB;
	struct s_light	*next;
}	t_light;

typedef struct s_camera
{
	t_v3			pos;
	t_v3			ori;
	t_v3			dir;
	int				FOV;
}	t_cam;

typedef struct s_obj
{
	char			*id;
	t_v3			pos;
	t_v3			ori;	
	t_v3			RGB;
	double			r;
	double			h;
	double			spec;
	struct	s_obj	*next;
}	t_obj;

typedef struct ray
{
	t_v3	o;
	t_v3	d;
}	t_ray;


typedef struct	s_data {
	void			*mlx;
	void			*mlx_win;
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	char			**matrix;
	double			width;
	double			height;
	double			*t;
	int				obj_size;
	double			closest_t;
	double			closest_s;

	t_cam			cam;
	t_light			*light;
	t_obj			*obj;
}	t_data;

/* UTILITY */

int		ft_error(char *str);
char	**ft_split(char const *s, char c);
double	ft_atof(const char *str);
char	*ft_strjoin(char *s1, char *s2);
int		check_arg(t_data *data);
t_v3	ret_vec(char *args);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup(const char *s1);

/* MLX_UTILITY */

int			create_trgb(int t, int r, int g, int b);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
int			ft_hooks(int keycode, t_data *data);
int			ft_init(t_data *data, int fd);

/* PARSING */

void	parse_buff(char *buff, t_data *data);
void	add_light(char	**args, t_data *data);
void	add_obj(char **args, t_data *data);

/* VEC OPERATIONS */

t_v3	sub_vec(t_v3 v1, t_v3 v2);
t_v3	normalize(t_v3 v1);
t_v3	mult_vec(t_v3 v1, t_v3 v2);
t_v3	add_vec(t_v3 v1, t_v3 v2);
t_v3	div_vec(t_v3 v1, t_v3 v2);
t_v3	mult_vec_n(t_v3 v1, double d);
t_v3	cross(t_v3 v1, t_v3 v2);
double	get_lenght(t_v3 *v1);
double	dot(t_v3 v1, t_v3 v2);
double	norm(t_v3 v1);

/* TRACING */

int		TraceRay(t_v3 O, t_v3 D, t_data *data);
void	ft_ray(t_data *data);
double	**rotation(t_data *data);
t_v3	get_direction(int x, int y, t_data *data);
double	computeLighting(t_v3 P, t_v3 N, t_data *data, t_obj *closest);

#endif