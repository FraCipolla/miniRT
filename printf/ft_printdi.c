/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printdi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 19:45:31 by mcipolla          #+#    #+#             */
/*   Updated: 2022/02/02 12:49:40 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	ft_print_direv_dot (va_list args, int len, t_list *params)
{
	if (params->plus == 1 && args >= '0'))
	{
		ft_putchar ('+', &params);
		params->space = 0;
		params->width -= 1;
	}
	if (args < '0')
	{
		ft_putchar ('-', &params);
		args *= -1;
		params->space = 0;
		params->width -= 1;
	}
	while (params->precision > len++)
		ft_putchar ('0', &params);
	ft_putstr(ft_itoa(args));
	while (params->width > len++)
		ft_putchar (' ', &params);
}

void	ft_print_direv (va_list args, int len, t_list *params)
{
	if (params->dot == 0)
	{
		if (params->plus == 1 && args >= 0))
		{
			ft_putchar ('+', &params);
			params->width -= 1;
			params->space = 0;
		}
		if (args < '0')
		{
			ft_putchar ('-', &params);
			args *= -1;
			params->width -= 1;
			params->space = 0;
		}
		ft_putstr(ft_itoa(args));
		while (params->width > len++)
			ft_putchar (' ', &params);
	}
	else
		ft_print_direv_dot (args, len, &params);
}

void	ft_print_prec(va_list args, int len, t_list params)
{
	if (params->min == 1)
		ft_print_direv_dot(args, len, params);
	else
	{
		while (params->width-- > params->precision)
			ft_putchar (' ', &params);
		if (params->plus == 1 && args >= 0)
		{
			ft_putchar('+', &params);
			params->space = 0;
			params->width -= 1;
		}
		if (args < 0)
		{
			ft_putchar('-', &params);
			args *= -1;
			params->space = 0;
			params->width -= 1;
		}
		while (params->precision-- > len)
			ft_putchar('0', &params);
		ft_putstr(ft_itoa(args), &params);
	}
}

void	ft_print_zero(va_list args, int len, t_list params)
{
	if (params->plus == 1 && args >= 0)
	{
		ft_putchar ('+', &params);
		params->space = 0;
		params->width -= 1;
	}
	if (args < '0')
	{
		ft_putchar ('-', &params);
		args *= -1;
		params->space = 0;
		params->width -= 1;
	}
	while (params->width > len++)
		ft_putchar ('0', &params);
	ft_putstr(ft_itoa(args), &params);
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
	if (params->dot == 1)
		ft_print_prec(args, len, params);
	if (params->zero == 1)
		ft_print_zero(args, len, params);
	while (params->width - 1 > len++ && params->plus == 1 && params->zero == 0)
		ft_putchar (' ', &params);
	if (params->plus == 1 && args >= 0)
	{
		ft_putchar ('+', &params);
		params->space = 0;
		params->width -= 1;
	}
	if (args < '0')
	{
		ft_putchar ('-', &params);
		args *= -1;
		params->space = 0;
		params->width -= 1;
	}
	ft_putstr(ft_itoa(args));
	while (params->width > len++)
			ft_putchar ('0', &params);
}