/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 19:45:35 by mcipolla          #+#    #+#             */
/*   Updated: 2022/02/01 11:11:22 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	ft_putchar_pf(char c)
{
		write (1, &c, 1);
}

void	ft_print_args (va_list args, t_list *params)
{
	if (params->di == 1)
		ft_print_di(args);
	if (params->u == 1)
	{
		params->plus = 0;
		ft_print_di(args);
	}
	if (params->x == 1)
		ft_print_x(args);
	if (params->X == 1)
		ft_print_X(args);
	if (params->s == 1)
		ft_print_s(args);
	if (params->c == 1)
		ft_print_c(args);
	if (params->p == 1)
		ft_print_p(args);
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
				if (ft_check_type(format[i]));
					break;
				tmp[c++] = format[i++];
			}
			ft_check_params(tmp);
			ft_print_args (args);
		}
		else
			ft_putchar_pf (format[i]);
		i++;
	}
}