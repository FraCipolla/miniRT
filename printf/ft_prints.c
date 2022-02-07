/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prints.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 23:54:07 by mcipolla          #+#    #+#             */
/*   Updated: 2022/02/07 11:36:54 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_s_rev(char *args, int len, t_list *params)
{
	int	c;

	c = -1;
	if (params->dot == 1 && params->prec < len)
	{
		while (++c < params->prec)
			ft_putchar(args[c], params);
		while (len++ <= params->width)
			ft_putchar(' ', params);
	}
	else
	{
		while (++c < len)
			ft_putchar(args[c], params);
		while (params->width > len++)
			ft_putchar (' ', params);
	}
}

void	ft_print_s_dot(char *args, int len, t_list *params)
{
	int	c;

	c = -1;
	if (params->prec < len)
	{
		while (len < params->width)
		{
			ft_putchar(' ', params);
			len++;
		}
		while (++c < params->prec)
			ft_putchar(args[c], params);
	}
	else
	{
		while (len < params->width--)
			ft_putchar(' ', params);
		while (++c < len)
			ft_putchar(args[c], params);
	}
}

void	ft_print_s(char *args, t_list *params)
{
	int		len;
	int		c;

	c = -1;
	len = 0;
	if (args == NULL)
		args = "(null)";
	while (args[len])
		len++;
	if (params->min == 1 || params->dot == 1)
	{
		if (params->min == 1)
			ft_print_s_rev(args, len, params);
		if (params->dot == 1)
			ft_print_s_dot(args, len, params);
		return ;
	}
	else if (params->dot == 0)
	{
		while (len++ < params->width)
			ft_putchar(' ', params);
		while (args[++c])
			ft_putchar(args[c], params);
	}
}
