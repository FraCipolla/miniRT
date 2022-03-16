/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 15:42:39 by mcipolla          #+#    #+#             */
/*   Updated: 2022/03/15 15:42:40 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_swap(int	*a, int *b)
{
	int	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	ft_swap_a(int *ar)
{
	write(1, "sa\n", 3);
	ft_swap(ar, ar + 1);
}

void	ft_swap_b(int *ar)
{
	write(1, "sb\n", 3);
	ft_swap(ar, ar + 1);
}

void	ft_swap_s(int *ar_a, int *ar_b)
{
	write(1, "ss\n", 3);
	ft_swap(ar_a, ar_a + 1);
	ft_swap(ar_b, ar_b + 1);
}
