/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 15:45:08 by mcipolla          #+#    #+#             */
/*   Updated: 2022/02/07 11:44:23 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_p(long unsigned int args, t_list *params)
{
	char			*tab;
	char			*str;
	unsigned int	len;

	str = "0123456789abcdef";
	tab = malloc(sizeof(char) * 35);
	len = 0;
	if (args == 0)
	{
		tab[0] = '0';
		len = 1;
	}
	while (args > 0)
	{
		tab[len] = str[args % 16];
		args = args / 16;
		len++;
	}
	tab[len] = '\0';
	if (params->hash == 1)
		params->width -= 2;
	ft_print_hex(tab, len, params);
	free(tab);
}
