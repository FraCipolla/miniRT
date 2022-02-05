/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prints.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 23:54:07 by mcipolla          #+#    #+#             */
/*   Updated: 2022/02/05 11:52:29 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
void	ft_print_s(char *args, t_list *params)
{
	int	len;
	int	c;

	c = -1;
	len = 0;
	while (args[len])
		len++;
	if (params->min == 1)
	{
		if (params->dot == 1)
		{
			while(++c < params->precision)
				ft_putchar(args[c], params);
			while (len++ <= params->width)
				ft_putchar(' ', params);
		}
		else
		{
			ft_putchar(args[len], params);
			while (params->width > len++)
				ft_putchar (' ', params);
		}
	}
	else if (params->dot == 1)
	{
		if (params->precision < len)
			{
				while (len++ <= params->width)
					ft_putchar(' ', params);
				while(++c < params->precision)
					ft_putchar(args[c], params);
			}
		else
			while(++c < len)
					ft_putchar(args[c], params);
	}
	else if (params->dot == 0)
	{
		while (len++ < params->width)
			ft_putchar(' ', params);
		while (args[++c])
			ft_putchar(args[c], params);
	}
}