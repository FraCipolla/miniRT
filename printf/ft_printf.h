#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <strings.h>
# include <stddef.h>
# include <stdarg.h>

typedef struct s_list
{
	int	min;
	int	zero;
	int	hash;
	int	dot;
	int	space;
	int	plus;
	int	precision;
	int	width;
	int	di;
	int	u;
	int	x;
	int	X;
	int	s;
	int	c;
	int	p;
	int	ret;
}				t_list;

int		ft_atoi(char *str);
char	*ft_itoa(int n);
void	ft_print_c(char args, t_list *params);
void	ft_print_di(long int args, t_list *params);
int		ft_printf(const char *format, ...);
void	ft_print_s(char *args, t_list *params);
void	ft_utility(t_list *params);
void	ft_find_width(char *str, t_list *params);
void	ft_find_precision(char *str, t_list *params);
void	ft_putchar(char c, t_list *params);
void	ft_itoa_hex(int n, t_list *params);
void	ft_putstr(char *s, t_list *params);
void	ft_print_direv (long int args, int len, t_list *params);
void	ft_check_params (char *str, t_list *params);
void	ft_print_hex(unsigned int args, t_list *params);
void	ft_print_p(long unsigned int args, t_list *params);
int		ft_check_type (char c, t_list *params);
void    put_nbr_hex(unsigned int n, char *str, t_list *params);
int		ft_type_val (char c);
int		ft_strlen(char *s);

#endif