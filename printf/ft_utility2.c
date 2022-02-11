/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utility2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:08:55 by mcipolla          #+#    #+#             */
/*   Updated: 2022/02/11 11:00:03 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_check_prec_dot(long int args, int len, t_list *params)
{
	if (params->min == 1)
	{
		ft_print_direv(args, len, params);
		return (1);
	}
	if (params->dot == 1)
	{
		ft_print_prec(args, len, params);
		return (1);
	}
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
