/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 23:53:34 by mcipolla          #+#    #+#             */
/*   Updated: 2022/02/07 10:22:53 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_c(char args, t_list *params)
{
	if (params->min == 1 && params->width > 1)
	{
		ft_putchar(args, params);
		while (params->width-- > 1)
			ft_putchar(' ', params);
	}
	else
	{
		while (params->width-- > 1)
			ft_putchar(' ', params);
		ft_putchar(args, params);
	}
}
