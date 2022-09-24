/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 14:23:37 by mcipolla          #+#    #+#             */
/*   Updated: 2022/09/24 15:12:42 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_global(int status)
{
	if (WIFEXITED(status) != 0)
	{
		g_exit = WEXITSTATUS(status);
	}
	else if (WIFSIGNALED(status) != 0 && WIFSIGNALED(status) == 1)
		g_exit = 130;
	else
		g_exit = 0;
}