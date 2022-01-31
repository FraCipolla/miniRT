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

int	ft_atoi(const char *str);
char	*ft_itoa(int n);
void	ft_print_c(va_list args);
void	ft_print_di(va_list args);
int	ft_printf(const char *format, ...);
void	ft_print_s(va_list args);
void	ft_utility(t_list *params);