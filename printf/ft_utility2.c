/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utility2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:08:55 by mcipolla          #+#    #+#             */
/*   Updated: 2022/02/07 11:57:10 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_type_val(char c)
{
	if (c == 'd' || c == 'i')
		return (1);
	else if (c == 'u')
		return (1);
	else if (c == 'x')
		return (1);
	else if (c == 'xx')
		return (1);
	else if (c == 's')
		return (1);
	else if (c == 'c')
		return (1);
	else if (c == 'p')
		return (1);
	else if (c == '%')
		return (1);
	return (0);
}

int	ft_strlen(char *s)
{
	int	n;

	n = 0;
	while (s[n])
		n++;
	return (n);
}

void	ft_putstr(char *s, t_list *params)
{
	int	i;

	i = -1;
	while (s[++i])
		ft_putchar(s[i], params);
}

void	ft_putchar(char c, t_list *params)
{
	write (1, &c, 1);
	params->ret += 1;
}

int	ft_atoi(char *str)
{
	int	i;
	int	sign;
	int	res;

	sign = 1;
	i = 0;
	res = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * sign);
}
