/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_hex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 11:18:25 by mcipolla          #+#    #+#             */
/*   Updated: 2022/02/02 16:40:32 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	put_nbr_hex(unsigned int n, char *str, t_list *params)
{
	if (n > 16)
		put_nbr_hex ((n / 16), str, params);
	ft_putchar (str[n % 16], params);
}

void	ft_itoa_hex(int n, t_list *params)
{
	unsigned int	nbr;
	char	*str;

	nbr = n;
	if (params->x == 1)
	{
		str = "0123456789abcdef";
		if (params->hash == 1)
			ft_putstr("0x", params);
	}
	else
	{
		str = "0123456789ABCDEF";
		if (params->hash == 1)
			ft_putstr("0X", params);
	}
	put_nbr_hex(nbr, str, params);
}