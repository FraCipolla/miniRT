/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movecount.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 17:24:10 by mcipolla          #+#    #+#             */
/*   Updated: 2022/05/11 17:24:10 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_direction(int *dir, int *moves, int size, int i)
{
	*dir = 0;
	*moves = i;
	if (i > size / 2)
	{
		*dir = 1;
		*moves = size - i;
	}
}

void	ft_moves_a(t_struct *data, t_best *best)
{
	int	i;
	int	j;
	int	x;

	x = 0;
	i = 0;
	while (i < data->size_a)
	{
		j = i + 1;
		if (j == data->size_a)
			j = 0;
		if (data->ar_a[i] < best->nb && data->ar_a[j] > best->nb)
		{
			best->na = data->ar_a[j];
			ft_direction(&best->dir_a, &best->moves_a, data->size_a, j);
			return ;
		}
		if (data->ar_a[i] == 1)
			x = i;
		i++;
	}
	best->na = 1;
	ft_direction(&best->dir_a, &best->moves_a, data->size_a, x);
}

void	ft_makestruc(t_best	*best, t_struct *data, int i)
{
	best->nb = data->ar_b[i];
	ft_direction(&best->dir_b, &best->moves_b, data->size_b, i);
	ft_moves_a(data, best);
	if (best->moves_a <= best->moves_b && best->dir_a == best->dir_b)
		best->count = best->moves_b;
	else if (best->moves_a > best->moves_b && best->dir_a == best->dir_b)
		best->count = best->moves_a;
	else if (best->dir_a != best->dir_b)
		best->count = best->moves_b + best->moves_a;
}

t_best	ft_findbest(t_struct *data)
{
	t_best	*best;
	t_best	min;
	int		i;

	best = (t_best *) malloc (sizeof(t_best) * data->size_b);
	i = 0;
	while (i < data->size_b)
	{
		ft_makestruc(&best[i], data, i);
		i++;
	}
	min = best[0];
	i = 1;
	while (i < data->size_b)
	{
		if (min.count > best[i].count)
			min = best[i];
		i++;
	}
	free(best);
	return (min);
}

void	ft_brainfuck(t_struct *data)
{
	t_best	best;
	int		*ara;
	int		*arb;

	best = ft_findbest(data);
	ara = data->ar_a;
	arb = data->ar_b;
	while ((ara[0] != best.na && arb[0] != best.nb) && best.dir_a == best.dir_b)
	{
		if (best.dir_a == 0)
			ft_rotate_r(data);
		else
			ft_rev_rotate_r(data);
	}
	while (ara[0] != best.na && best.dir_a == 0)
		ft_rotate_a(data);
	while (ara[0] != best.na && best.dir_a == 1)
		ft_rev_rotate_a(data);
	while (arb[0] != best.nb && best.dir_b == 0)
		ft_rotate_b(data);
	while (arb[0] != best.nb && best.dir_b == 1)
		ft_rev_rotate_b(data);
	ft_push_a(data);
}
