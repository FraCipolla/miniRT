#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include "basics.h"

# define IMG_SIZE 34
typedef enum	e_tiletype
{
	EMPTY = '0',
	WALL = '1',
	COLLECTABLE = 'C',
	PLAYER = 'P',
	EXIT = 'E',
	ENEMY = 'M',
	FOLLOWER = 'F',
}	t_tiletype;

typedef struct s_tile
{
	t_tiletype	type;
	t_tiletype	og_type;
	t_vector	position;
	struct s_tile	*up;
	struct s_tile	*down;
	struct s_tile	*left;
	struct s_tile	*right;	
}	t_tile;

/*	PLAYER */
typedef struct s_player
{
	t_tile	*tile;
	void	*current_img;
	int		framecount;
	int		idle_frames;
	void	*idle_img_0;
	void	*idle_img_1;
	int		action_frames;
	void	*action_img;
}	t_player;

/*	ENEMY */
typedef struct s_enemy
{
	t_enemytype		type;
	int				dir;
	t_tile			*og_tile;
	t_tile			*tile;
	struct s_enemy	*next;
}	t_enemy;

/*	INPUT	*/
enum	e_keycode
{
	KEY_UP = 13,
	KEY_DOWN = 1,
	KEY_LEFT = 0,
	KEY_RIGHT = 2,
	RESET = 15,
	ESC = 53
};

typedef struct s_game
{
	void		*mlx;
	void		*window;
	t_vector	window_size;
	t_tile		**tilemap;
	
	t_player	player;

	int			og_collects;
	int			collects;
	int			moves;

	t_enemy		*enemy_list;

	// sprites/images
	t_vector		img_size;
	t_wall_img		wall_imgs;
	t_collect_img	collects_imgs;
	t_enemy_img		enemy_imgs;
	void			*door_open_img;
	void			*door_close_img;
	t_effect		effect;
	void			*red_panel;
	void			*white_panel;
}	t_game;

#endif