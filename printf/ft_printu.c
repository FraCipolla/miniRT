/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 10:54:18 by mcipolla          #+#    #+#             */
/*   Updated: 2022/02/06 20:44:38 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_udirev (long int args, int len, t_list *params)
{
	int	c;

	c = args;
	if (params->dot == 0)
	{
		if (params->plus == 1 && args >= 0)
		{
			ft_putchar ('+', params);
			params->space = 0;
			params->width -= 1;
		}
		if (params->u == 1)
			ft_utoa(args, params);
		while (params->width > len++)
			ft_putchar (' ', params);
	}
	else
		ft_print_direv_dot (args, len, params);
}

void	ft_print_uprec(unsigned int args, int len, t_list *params)
{
	if (params->min == 1)
		ft_print_direv_dot(args, len, params);
	else
	{
		if (params->width > params->precision)
			while (params->width-- > params->precision && params->precision > len)
				ft_putchar (' ', params);
		if (params->plus == 1 && args >= 0)
		{
			ft_putchar('+', params);
			params->space = 0;
			params->width -= 1;
		}
		while (params->precision-- > len)
			ft_putchar('0', params);
		if (params->u == 1)
			ft_utoa(args, params);
	}
}
void	ft_print_u(unsigned int args, t_list *params)
{
	int			len;
	unsigned int size;
	
	len = 1;
	size = args;
	while ((size /= 10) != 0)
		len++;
	if (params->width > len && params->dot == 0 && params->min == 0 && params->zero == 0)
		while (len++ < params->width)
			ft_putchar(' ', params);
	if (params->dot == 1)
	{
		ft_print_uprec(args, len, params);
		return ;
	}
	if (params->min == 1)
	{
		ft_print_udirev (args, len, params);
		return ;
	}
	while (params->width > len++)
			ft_putchar ('0', params);
	ft_utoa(args, params);
}