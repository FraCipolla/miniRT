/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prints.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 23:54:07 by mcipolla          #+#    #+#             */
/*   Updated: 2022/02/04 18:59:52 by mcipolla         ###   ########.fr       */
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
	if (params->dot == 1)
	{
		printf("WIDTH: %d\n", params->width);
		//printf("PREC: %d\n", params->precision);
		//printf("LEN: %d\n", len);
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
	if (params->min == 1)
	{
		printf("WIDTH: %d\n", params->width);
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
}