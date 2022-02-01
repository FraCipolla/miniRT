/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_hex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 11:18:25 by mcipolla          #+#    #+#             */
/*   Updated: 2022/02/01 11:30:47 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	put_nbr_hex(long int n, t_list *params)
{
	char	*str;

	if (params->x == 1)
		str = "0123456789abcdef";
	else
		str = "0123456789ABCDEF";
	if (n > 16)
		put_nbr_hex (n / 16, params);
	ft_putchar (&str[n % 16])
}

void	*ft_itoa_hex(int n)
{
	long int	nbr;

	nbr = n;
	if (nbr < 0)
	{
		ft_putchar('-');
		nbr = nbr * -1;
	}
	put_nbr_hex(nbr);
}