/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 10:32:13 by mcipolla          #+#    #+#             */
/*   Updated: 2022/02/11 10:58:03 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <strings.h>
# include <stddef.h>
# include <stdarg.h>
# include <limits.h>

typedef struct s_list
{
	int	min;
	int	zero;
	int	hash;
	int	dot;
	int	space;
	int	plus;
	int	prec;
	int	width;
	int	di;
	int	u;
	int	x;
	int	xx;
	int	s;
	int	c;
	int	p;
	int	ret;
	int	percent;
}				t_list;

int		ft_atoi(char *str);
void	ft_itoa(int n, t_list *params);
void	ft_print_c(char args, t_list *params);
void	ft_print_di(long int args, t_list *params);
int		ft_printf(const char *format, ...);
void	ft_print_s(char *args, t_list *params);
void	ft_utility(t_list *params);
void	ft_find_width(char *str, t_list *params);
void	ft_find_precision(char *str, t_list *params);
void	ft_putchar(char c, t_list *params);
void	ft_putstr(char *s, t_list *params);
void	ft_print_direv(long int args, int len, t_list *params);
void	ft_check_params(char *str, t_list *params);
void	ft_print_hex(char *str, int len, t_list *params);
void	ft_print_p(long unsigned int args, t_list *params);
int		ft_check_type(char c, t_list *params);
char	put_nbr_hex(unsigned int n, char *str, t_list *params);
int		ft_type_val(char c);
int		ft_strlen(char *s);
void	ft_itoa_hex(unsigned int n, t_list *params);
void	ft_utoa(unsigned int n, t_list *params);
void	ft_print_u(unsigned int args, t_list *params);
void	ft_print_prec(long int args, int len, t_list *params);
void	ft_print_direv_dot(long int args, int len, t_list *params);
void	ft_print_args(va_list args, t_list *params);
void	ft_putstr_free(char *s, t_list *params);
int		ft_check_prec_dot(long int args, int len, t_list *params);

#endif