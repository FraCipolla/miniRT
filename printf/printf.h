#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <strings.h>
# include <stddef.h>

typedef struct s_list
{
	int	min;
	int	zero;
	int	hash;
	int	dot;
	int	space;
	int	plus;
	int	precision;
	int	witdh;
	int	di;
	int	u;
	int	x;
	int	X;
	int	s;
	int	c;
	int	p;
}				t_list;