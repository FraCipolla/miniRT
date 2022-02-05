/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 19:45:35 by mcipolla          #+#    #+#             */
/*   Updated: 2022/02/05 18:07:40 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

void	ft_print_args(va_list args, t_list *params)
{
	if (params->di == 1)
		ft_print_di(va_arg(args, unsigned int), params);
	else if (params->u == 1)
	{
		params->plus = 0;
		ft_print_di(va_arg(args, unsigned int), params);
	}
	else if (params->x == 1 || params->X == 1)
		ft_itoa_hex(va_arg(args, unsigned int), params);
	else if (params->s == 1)
		ft_print_s(va_arg(args, char *), params);
	else if (params->c == 1)
		ft_print_c(va_arg(args, int), params);
	else if (params->p == 1)
		ft_print_p(va_arg(args, long unsigned int), params);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	char	*tmp;
	int		i;
	int		c;
	t_list params;

	va_start (args, format);
	i = -1;
	while (format[++i])
	{
		if (format[i] == '%')
		{
			ft_utility(&params);
			i++;
			c = 0;
			while (ft_check_type (format[i], &params) == 0)
			{
				if (params.percent == 1)
					break ;	
				tmp[c++] = format[i++];	
			}
			tmp[c] = '\0';
			ft_check_params(tmp, &params);
			ft_print_args(args, &params);
		}
		else
			ft_putchar (format[i], &params);
	}
	va_end (args);
	return (params.ret);
}