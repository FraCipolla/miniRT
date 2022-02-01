/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 19:45:35 by mcipolla          #+#    #+#             */
/*   Updated: 2022/02/01 11:50:47 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	ft_putchar(char c)
{
		write (1, &c, 1);
}

void	ft_print_args (va_list args, t_list *params)
{
	if (params->di == 1)
		ft_print_di(args, params);
	if (params->u == 1)
	{
		params->plus = 0;
		ft_print_di(args, params);
	}
	if (params->x == 1)
		ft_print_x(args, params);
	if (params->X == 1)
		ft_print_X(args, params);
	if (params->s == 1)
		ft_print_s(args, params);
	if (params->c == 1)
		ft_print_c(args, params);
	if (params->p == 1)
		ft_print_p(args, params);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	char *tmp;
	int	i;
	int	c;

	va_start (args, format);
	i = 0;
	while (format[i])
	{
		if (format[i - 1] == '%')
		{
			c = 0;
			while (format[i] != '\0' || format[i + 1] != '%')
			{
				if (ft_check_type(format[i], params));
					break;
				tmp[c++] = format[i++];
			}
			ft_check_params(tmp, params);
			ft_print_args (args, params);
		}
		else
			ft_putchar (format[i]);
		i++;
	}
}