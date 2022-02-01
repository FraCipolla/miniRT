/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printdi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 19:45:31 by mcipolla          #+#    #+#             */
/*   Updated: 2022/02/01 11:46:12 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	ft_print_direv_dot (va_list args, int len, t_list *params)
{
	if (params->dot == 1)
	{
		if (params->plus == 1 && args >= '0'))
		{
			ft_putchar ('+');
			params->space = 0;
			params->width -= 1;
		}
		if (args < '0')
		{
			ft_putchar ('-');
			args *= -1;
			params->space = 0;
			params->width -= 1;
		}
		while (params->precision > len++)
			ft_putchar ('0');
		ft_putstr(ft_itoa(args));
		while (params->width > len++)
			ft_putchar (' ');
	}
}

void	ft_print_direv (va_list args, int len, t_list *params)
{
	if (params->dot == 0)
	{
		if (params->plus == 1 && args >= '0'))
		{
			ft_putchar ('+');
			params->space = 0;
			params->width -= 1;
		}
		if (args < '0')
		{
			ft_putchar ('-');
			args *= -1;
			params->space = 0;
			params->width -= 1;
		}
		ft_putstr(ft_itoa(args));
		while (params->width > len++)
			ft_putchar (' ');
	}
	else
		ft_print_direv_dot (args, len, params);
	params->zero = 0;
}

void	ft_print_precision (va_list args, t_list *params)
{
	params->precision -= params->width;

	while (params->precision > 0)
	{
		ft_putchar('0');
		params->precision -= 1;
	}
}

void	ft_print_di(va_list args, t_list *params)
{
	int	len;

	len = 0;
	while (args != 0)
	{
		args /= 10;
		len++;
	}
	if (params->min == 1)
	{
		ft_print_direv (args, len, params);
		return ;
	}
	while (params->width - 1 > len++ && params->plus == 1 && params->zero == 0)
		ft_putchar (' ');
	if (params->plus == 1 && args >= '0')
	{
		ft_putchar ('+');
		params->space = 0;
		params->width -= 1;
	}
	if (args < '0')
	{
		ft_putchar ('-');
		args *= -1;
		params->space = 0;
		params->width -= 1;
	}
	while (params->width > len++)
			ft_putchar ('0');
	}
	ft_putstr(ft_itoa(args));
}