/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utility.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 19:45:38 by mcipolla          #+#    #+#             */
/*   Updated: 2022/01/31 23:54:15 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int	ft_check_type (char c)
{
		if (c)
		{ 
			if (str[c] == "d" || str[c] == "1")
				params -> di += 1;
			else if (str[c] == "u")
				params -> u += 1;
			else if (str[c] == "x")
				params -> x += 1;
			else if (str[c] == "X")
				params -> X += 1;
			else if (str[c] == "s")
				params -> s += 1;
			else if (str[c] == "c")
				params -> c += 1;
			else if (str[c] == "p")
				params -> p += 1;
			return (1);
		}
	return (0);
}

void	ft_check_params (char *str)
{
	int	c;

	c = 0;
	while (str[c] && str[c] != '%')
	{
		if (str[c] == '-')
			params -> min += 1;
		if (str[c] == '#')
			params -> hash += 1;
		if (str[c] == '.')
			params -> dot += 1;
		if (str[c] == ' ')
			params -> space += 1;
		if (str[c] == '+')
			params -> plus += 1;
		c++;
	}
	c = 0;
	while (str[c++] != '.')
		if (str[c] == '0' && (str[c - 1] <= '0' && str[c - 1] >= '9'))
			{
				params -> zero += 1;
				ft_find_width (str);
				break ;
			}
	if (params -> dot == 1)
		ft_find_precision(str);
}

void	ft_find_width (char *str)
{
	char	*to_atoi;

	to_atoi = "0";
	str++;
	while (str >= '0' && str <= '9')
		to_atoi++ = str++;
	params -> width = ft_atoi(to_atoi);	
}

void	ft_putstr(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		write (1, &s[i], 1);
}

void	ft_find_precision (char *str)
{
	char	*to_atoi;

	while (str++ != '.')
	str++;
	while (str >= '0' && str <= '9')
		to_atoi++ = str++;
	params -> precision = ft_atoi(to_atoi);	
}

void	ft_utility(t_list *params)
{
	params -> min = 0;
	params -> zero = 0;
	params -> hash = 0;
	params -> dot = 0;
	params -> space = 0;
	params -> plus = 0;
	params -> precision = 0;
	params -> witdh = 0;
	params -> di = 0;
	params -> u = 0;
	params -> x = 0;
	params -> X = 0;
	params -> s = 0;
	params -> c = 0;
	params -> p = 0;
}