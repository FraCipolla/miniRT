/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 17:24:15 by mcipolla          #+#    #+#             */
/*   Updated: 2022/05/11 17:24:15 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>

typedef struct s_best
{
	int	count;
	int	moves_a;
	int	moves_b;
	int	na;
	int	nb;
	int	dir_a;
	int	dir_b;
}				t_best;

typedef struct s_struct
{
	int		*ar_a;
	int		*ar_b;
	int		*ar_best;
	int		size_a;
	int		size_b;
	int		size_best;
}				t_struct;

void	ft_swap(int	*a, int *b, int size);
void	ft_swap_a(int *ar, int size);
void	ft_swap_b(int *ar, int size);
void	ft_swap_s(int *ar_a, int *ar_b, int size);
void	ft_push(int *ar_1, int *ar_2, int *size_1, int *size_2);
void	ft_push_a(t_struct *data);
void	ft_push_b(t_struct *data);
void	ft_rotate(int *ar, int size);
void	ft_rotate_a(t_struct *data);
void	ft_rotate_b(t_struct *data);
void	ft_rotate_r(t_struct *data);
void	ft_rev_rotate(int *ar, int size);
void	ft_rev_rotate_a(t_struct *data);
void	ft_rev_rotate_b(t_struct *data);
void	ft_rev_rotate_r(t_struct *data);
int		*ft_multi_init(char **matrix, int size);
int		*ft_mono_init(char *args, int *size);
int		ft_multi_check(char **matrix, int size);
int		ft_checkfordoubles(int *ar, int size);
void	ft_checkmalloc(void *ptr);
void	ft_check_max(char *str);
int		ft_order(int *ar, int size);
void	ft_error(void);
int		ft_strcmp(char *s1, char *s2);
int		*ft_ardup(int *ar, int size);
void	ft_freematrix(int **matrix, int size);
void	ft_sort_ar(int *ar, int size);
//void	ft_printarray(int *ar, int size);
void	ft_findcomb(t_struct *data);
int		ft_min(int *array, int size);
int		ft_findind(int nb, int *array, int size);
int		ft_findindmin(int *array, int size);
void	ft_brainfuck(t_struct *data);

#endif