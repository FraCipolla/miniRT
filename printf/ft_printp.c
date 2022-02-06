/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 15:45:08 by mcipolla          #+#    #+#             */
/*   Updated: 2022/02/06 11:50:42 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
void	ft_print_p(long unsigned int args, t_list *params)
{
    char	*tab;
    char    *str;
    unsigned int     len;

    len = 0;
    str = "0123456789abcdef";
    tab = malloc(sizeof(char) * 35);
    while (args > 0)
	{
		tab[len] = str[args % 16];
		args = args / 16;
		len++;
	}
	tab[len] = '\0';
    params->hash = 0;
    params->width -= 2;
	ft_print_hex(tab, len, params);
	free(tab);
}