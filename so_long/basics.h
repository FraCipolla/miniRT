/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basics.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 14:36:33 by mcipolla          #+#    #+#             */
/*   Updated: 2022/02/12 14:39:36 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASICS_H
# define BASICS_H

# include "libft/libft.h"
# include <stdio.h>

typedef enum e_bool
{
	TRUE = 1,
	FALSE = 0
}	t_bool;

typedef struct s_vector
{
	int	x;
	int	y
}	t_vector;

int		error(char *message);
void	*null_error(char *message);
void	print_warning(char *message);

#endif