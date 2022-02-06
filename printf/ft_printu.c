/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 10:54:18 by mcipolla          #+#    #+#             */
/*   Updated: 2022/02/06 18:47:16 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_u(unsigned args, t_list *params)
{
	int	len;
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
		ft_print_prec(args, len, params);
		return ;
	}
	if (params->min == 1)
	{
		ft_print_direv (args, len, params);
		return ;
	}
	while (params->width > len++)
			ft_putchar ('0', params);
	ft_utoa(args, params);
}