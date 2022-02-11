/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printxX.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 23:56:55 by mcipolla          #+#    #+#             */
/*   Updated: 2022/02/10 12:21:02 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	check_prefix(t_list *params)
{
	if (params->p == 1)
	{
		ft_putstr("0x", params);
		params->width -= 2;
	}
	if (params->hash == 1 && params->p == 0)
	{
		if (params->x == 1)
			ft_putstr("0x", params);
		else
			ft_putstr("0X", params);
	}
}

void	ft_print_hex_rev(char *str, int len, t_list *params)
{
	int	c;

	c = len;
	if (params->dot == 0)
	{
		check_prefix(params);
		while (len-- > 0)
			ft_putchar(str[len], params);
		while (params->width-- > c)
			ft_putchar(' ', params);
	}
	if (params->dot == 1)
	{
		c = params->prec;
		check_prefix(params);
		while (params->prec-- > len)
			ft_putchar('0', params);
		while (len-- > 0)
			ft_putchar(str[len], params);
		while (params->width-- > c)
			ft_putchar(' ', params);
	}
}

void	ft_print_hex(char *str, int len, t_list *params)
{
	if (params->min == 1)
	{
		ft_print_hex_rev(str, len, params);
		return ;
	}
	if (params->dot == 0)
	{
		while (params->zero == 1 && params->width-- > len)
			ft_putchar ('0', params);
		while (params->width-- > len && params->zero == 0)
			ft_putchar(' ', params);
		check_prefix(params);
		while (len-- > 0)
			ft_putchar(str[len], params);
	}
	if (params->dot == 1)
	{
		while (params->width-- > params->prec)
			ft_putchar(' ', params);
		check_prefix(params);
		while (params->prec-- > len)
			ft_putchar('0', params);
		while (len-- > 0)
			ft_putchar(str[len], params);
	}
}

void	ft_itoa_hex(unsigned int n, t_list *params)
{
	char	*str;
	int		len;
	char	*tab;

	len = 0;
	tab = malloc(sizeof(char) * 35);
	if (n == 0)
	{
		tab[0] = '0';
		len = 1;
		params->hash = 0;
	}
	if (params->x == 1)
		str = "0123456789abcdef";
	else
		str = "0123456789ABCDEF";
	while (n > 0)
	{
		tab[len] = str[n % 16];
		n = n / 16;
		len++;
	}
	tab[len] = '\0';
	ft_print_hex(tab, len, params);
	free(tab);
}
