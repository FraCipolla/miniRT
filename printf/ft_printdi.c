/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printdi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 19:45:31 by mcipolla          #+#    #+#             */
/*   Updated: 2022/02/14 16:17:59 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_direv_dot(long int args, int len, t_list *params)
{
	if (params->plus == 1 && args >= 0)
	{
		ft_putchar ('+', params);
		params->space = 0;
		params->width -= 1;
	}
	if (args < 0)
	{
		ft_putchar ('-', params);
		args *= -1;
		params->space = 0;
		params->width -= 1;
	}
	while (params->prec > len++)
		ft_putchar ('0', params);
	if (params->u == 1)
		ft_utoa(args, params);
	else
		ft_itoa(args, params);
	while (params->width >= len++)
		ft_putchar (' ', params);
}

void	ft_print_direv(long int args, int len, t_list *params)
{
	int	c;

	c = args;
	if (params->dot == 1)
	{
		ft_print_direv_dot (args, len, params);
		return ;
	}
	if (params->plus == 1 && args >= 0)
	{
		ft_putchar ('+', params);
		params->space = 0;
		params->width -= 1;
	}
	if (c < 0 && args != INT_MIN)
	{
		ft_putchar ('-', params);
		args *= -1;
		params->space = 0;
		params->width -= 1;
	}
	if (params->u == 1)
		ft_utoa(args, params);
	else
		ft_itoa(args, params);
	while (params->width > len++)
		ft_putchar (' ', params);
}

void	ft_print_prec(long int args, int len, t_list *params)
{
	int	c;

	c = args;
	if (params->width > params->prec)
		while (params->width-- > params->prec && params->prec > len)
			ft_putchar (' ', params);
	if (params->plus == 1 && args >= 0)
	{
		ft_putchar('+', params);
		params->space = 0;
		params->width -= 1;
	}
	if (c < 0)
	{
		ft_putchar('-', params);
		args *= -1;
		params->space = 0;
		params->width -= 1;
	}
	while (params->prec-- > len)
		ft_putchar('0', params);
	if (params->u == 1)
		ft_utoa(args, params);
	else
		ft_itoa(args, params);
}

void	check_sign(long int args, t_list *params)
{
	int	c;

	c = args;
	if (args == LONG_MIN)
		args = 0;
	if (params->plus == 1 && c >= 0)
	{
		ft_putchar ('+', params);
		params->space = 0;
		params->width -= 1;
	}
	if (c < 0)
	{
		ft_putchar ('-', params);
		params->space = 0;
		params->width -= 1;
	}
}

void	ft_print_di(long int args, t_list *params)
{
	int	len;
	int	size;

	len = 0;
	size = args;
	if (args == LONG_MIN)
		args = 0;
	if (size == 0)
		len = 1;
	while (size != 0)
	{
		size /= 10;
		len++;
	}
	if (ft_check_prec_dot(args, len, params) == 1)
		return ;
	if (params->width > len && params->zero == 0)
		while (++len < params->width)
			ft_putchar(' ', params);
	check_sign(args, params);
	while (params->width > len++)
		ft_putchar ('0', params);
	if (params->space == 1)
		ft_putchar(' ', params);
	ft_itoa(args, params);
}
