/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utility.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 19:45:38 by mcipolla          #+#    #+#             */
/*   Updated: 2022/02/02 19:21:50 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int	ft_check_type (char c, t_list *params)
{
		if (c)
		{ 
			if (c == 'd' || c == 'i')
				params->di += 1;
			else if (c == 'u')
				params->u += 1;
			else if (c == 'x')
				params->x += 1;
			else if (c == 'X')
				params->X += 1;
			else if (c == 's')
				params->s += 1;
			else if (c == 'c')
				params->c += 1;
			else if (c == 'p')
				params->p += 1;
			return (1);
		}
	return (0);
}

void	ft_check_params (char *str, t_list *params)
{
	int	c;

	//printf("PARAMS %s\n", str);
	c = 0;
	if (str)
	{
		while (str[c] && str[c] != '%')
		{
			if (str[c] == '-')
				params->min += 1;
			if (str[c] == '#')
				params->hash += 1;
			if (str[c] == '.')
				params->dot += 1;
			if (str[c] == ' ')
				params->space += 1;
			if (str[c] == '+')
				params->plus += 1;
			c++;
		}
	}
	c = 0;
	while (params->dot == 1 && str[c] != '.' && str[c])
	{
		if (str[c] == '0' && (str[c - 1] <= '0' && str[c - 1] >= '9'))
			{
				params->zero += 1;
				ft_find_width (str, params);
				break ;
			}
		c++;
	}
	//printf("END\n");
	if (params->dot == 1)
		ft_find_precision(str, params);
}

void	ft_find_width (char *str, t_list *params)
{
	char	*to_atoi;
	int		i;

	to_atoi = "0";
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
		to_atoi[i] = str[i];
	params->width = ft_atoi(to_atoi);	
}

void	ft_putstr(char *s, t_list *params)
{
	int	i;

	i = -1;
	while (s[++i])
		ft_putchar(s[i], params);
}

void	ft_find_precision (char *str, t_list *params)
{
	char	*to_atoi;
	int		i;
	int 	c;

	i = 0;
	c = 0;
	while (str[i] != '.')
		i++;
	i++;
	while (str[i] >= '0' && str[i] <= '9')
		to_atoi[c] = str[i];
	params->precision = ft_atoi(to_atoi);	
}

void	ft_utility(t_list *params)
{
	params->min = 0;
	params->zero = 0;
	params->hash = 0;
	params->dot = 0;
	params->space = 0;
	params->plus = 0;
	params->precision = 0;
	params->width = 0;
	params->di = 0;
	params->u = 0;
	params->x = 0;
	params->X = 0;
	params->s = 0;
	params->c = 0;
	params->p = 0;
	params->ret = 0;
}