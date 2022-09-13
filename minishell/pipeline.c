/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 14:17:48 by mcipolla          #+#    #+#             */
/*   Updated: 2022/09/07 14:20:17 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	status(int n)
{
	int	exit_value;

	exit_value = n;
	return (n);
}

void	pipex(t_px *px, char **envp)
{
	int	i;
	int	status;

	i = 0;
	if (px->heredoc == 1)
		heredoc_child(px, envp, i, px->mycmdargs[i]);
	else
		child_1(px, envp, i, px->mycmdargs[i]);
	while (++i < px->n_cmd - 1)
	{
		child_mid(px, envp, i, px->mycmdargs[i]);
	}
	child_last(px, envp, i, px->mycmdargs[i]);
	i = -1;
	while (++i < px->n_cmd)
		waitpid(px->pid[i], &status, 0);
}