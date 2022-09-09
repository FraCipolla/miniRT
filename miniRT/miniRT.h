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

typedef struct s_mat4x4
{
	double	m[4][4];
}	t_mat4x4;

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
	t_v3			up;
	t_v3			u;
	t_v3			v;
	t_v3			w;
	t_v3			screen_center;
	t_mat4x4		world;
	double			lenght;
	double			horizontal_size;
	double			aspectRatio;
	double			FOV;
	double			view_range;
	t_v3			lookAt;
}	t_cam;

typedef struct s_ray
{
	t_v3		origin;
	t_v3		dir;
	double		min;
	double		max;
}	t_ray;

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
	int				obj_size;
	double			closest_t;
	double			closest_s;
	t_ray			ray;
	t_obj			*closest_obj;
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
int		camera_init(char **args, t_cam *cam);

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

/* MATRIX OPERATIONS */

t_v3	mult_vec_by_matrix(t_v3 vec, double **matrix);
double	**rot_matrix(t_v3 rot, t_v3 dir);
t_mat4x4	mat4x4(t_v3 origin, t_v3 forward, t_v3 right, t_v3 up);
t_mat4x4	look_at(t_v3 origin, t_v3 dir);
t_v3	mat4_get(t_mat4x4 m4, int get);
t_v3	mat4_mult_dir(t_mat4x4 matrix, t_v3 dir);

/* TRACING */

int		TraceRay(t_v3 O, t_v3 D, t_data *data);
void	ft_ray(t_data *data);
double	**rotation(t_data *data);
t_ray	get_direction(int x, int y, t_data *data);
double	computeLighting(t_v3 P, t_v3 N, t_data *data, t_obj *closest);
double	IntersectPlane(t_v3 O, t_v3 D, t_obj *plane, double t);
double	IntersectCylinder(t_v3 O, t_v3 D, t_obj *cyl, double t);
double	IntersectRaySphere(t_v3 O, t_v3 D, t_obj *sphere, double t);
#endif