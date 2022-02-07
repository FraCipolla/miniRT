/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 19:45:35 by mcipolla          #+#    #+#             */
/*   Updated: 2022/02/07 12:57:04 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_type_val(char c)
{
	if (c == 'd' || c == 'i')
		return (1);
	else if (c == 'u')
		return (1);
	else if (c == 'x')
		return (1);
	else if (c == 'X')
		return (1);
	else if (c == 's')
		return (1);
	else if (c == 'c')
		return (1);
	else if (c == 'p')
		return (1);
	else if (c == '%')
		return (1);
	return (0);
}

void	ft_print_args(va_list args, t_list *params)
{
	if (params->u == 1)
	{
		params->plus = 0;
		ft_print_u(va_arg(args, unsigned int), params);
	}
	else if (params->di == 1)
		ft_print_di(va_arg(args, long int), params);
	else if (params->x == 1 || params->xx == 1)
		ft_itoa_hex(va_arg(args, unsigned int), params);
	else if (params->s == 1)
		ft_print_s(va_arg(args, char *), params);
	else if (params->c == 1)
		ft_print_c(va_arg(args, int), params);
	else if (params->p == 1)
		ft_print_p(va_arg(args, long unsigned int), params);
}

char	*ft_make_malloc(const char *format, int i, t_list *params)
{
	int		c;
	char	*tmp;
	int		b;

	c = 0;
	b = i;
	ft_utility(params);
	while (ft_check_type (format[b++], params) == 0)
		c++;
	tmp = malloc(sizeof(char) * b + 1);
	c = 0;
	while (ft_check_type (format[i], params) == 0 && format[i] != '%')
		tmp[c++] = format[i++];
	tmp[c] = '\0';
	ft_check_params(tmp, params);
	if (params->percent == 1)
		ft_putchar('%', params);
	return (tmp);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	char	*tmp;
	int		i;
	t_list	params;

	va_start (args, format);
	params.ret = 0;
	i = -1;
	while (format[++i])
	{
		if (format[i] == '%')
		{
			i++;
			tmp = ft_make_malloc(format, i, &params);
			while (ft_check_type (format[i], &params) == 0 && format[i] != '%')
				i++;
			ft_print_args(args, &params);
			free(tmp);
		}
		else
			ft_putchar (format[i], &params);
	}
	va_end (args);
	return (params.ret);
}
