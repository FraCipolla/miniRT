/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 17:35:18 by mcipolla          #+#    #+#             */
/*   Updated: 2022/02/07 11:58:41 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	find_size(long int n)
{
	int	c;

	c = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		n *= -1;
	while (n != 0)
	{
		n /= 10;
		c++;
	}
	return (c);
}

void	put_nbr(char *tab, long int n, int size)
{
	if (n < 0)
		n *= -1;
	if (n > 9)
		put_nbr (tab, n / 10, size -1);
	tab[size] = (n % 10 + '0');
}

void	ft_itoa(int n, t_list *params)
{
	int			size;
	char		*tab;
	long int	nbr;

	nbr = n;
	if (nbr == LONG_MIN)
		nbr = 0;
	if (nbr < 0)
		nbr *= -1;
	if (nbr < 0)
		size = find_size(nbr) + 1;
	else
		size = find_size(nbr);
	tab = (char *)malloc(sizeof(char) * size + 1);
	if (!tab)
		return ;
	tab[size] = 0;
	if (nbr < 0)
	{
		tab[0] = '-';
		params->width -= 1;
	}
	put_nbr(tab, nbr, size - 1);
	ft_putstr(tab, params);
	free(tab);
}

void	ft_utoa(unsigned int n, t_list *params)
{
	int				size;
	char			*tab;
	unsigned int	nbr;

	nbr = n;
	if (nbr < 0)
		size = find_size(nbr) + 1;
	else
		size = find_size(nbr);
	tab = (char *)malloc(sizeof(char) * size + 1);
	if (!tab)
		return ;
	tab[size] = 0;
	if (nbr < 0)
	{
		tab[0] = '-';
		nbr = nbr * -1;
	}
	put_nbr(tab, nbr, size - 1);
	ft_putstr(tab, params);
	free(tab);
}
