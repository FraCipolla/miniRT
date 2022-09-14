/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 17:51:30 by mcipolla          #+#    #+#             */
/*   Updated: 2022/07/20 23:20:38 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_1(int **end, int i, char **mypath, char **cmd)
{
	int	stdout_cpy;

	stdout_cpy = dup(1);
	if (fork() == 0)
	{
		close(end[i][0]);
		// dup2(f1, STDIN_FILENO);
		dup2(end[i][1], STDOUT_FILENO);
		close(end[i][1]);
		make_fork(mypath, cmd);
		dup2(stdout_cpy, 1);
		// write(1, "ERROR: invalid command\n", 24);
		exit(0);
	}
	else
	{
		// close(f1);
		close(end[0][1]);
	}
}

void	child_mid(int **end, int i, char **mypath, char **cmd)
{
	int	stdout_cpy;

	stdout_cpy = dup(1);
	if (fork() == 0)
	{
		close(end[i][0]);
		dup2(end[i - 1][0], STDIN_FILENO);
		dup2(end[i][1], STDOUT_FILENO);
		close(end[i - 1][0]);
		close(end[i][1]);
		make_fork(mypath, cmd);
		dup2(stdout_cpy, 1);
		// write(1, "ERROR: invalid command\n", 24);
		exit(0);
	}
	else
	{
		close(end[i - 1][0]);
		close(end[i][1]);
	}
}

void	child_last(int **end, int i, char **mypath, char **cmd)
{
	int	stdout_cpy;

	stdout_cpy = dup(1);
	if (fork() == 0)
	{
		close(end[i - 1][1]);
		dup2(end[i - 1][0], STDIN_FILENO);
		dup2(stdout_cpy, STDOUT_FILENO);
		close(end[i - 1][0]);
		// close(f2);
		make_fork(mypath, cmd);
		dup2(stdout_cpy, 1);
		// write(1, "ERROR: invalid command\n", 24);
		exit(0);
	}
	else
	{
		// close(f2);
		close(end[i - 1][0]);
	}
}

void	pipex(int **end, char **pipes, char **mypath, int n_pipes)
{
	int	i;
	char	**args;

	i = 0;
	args = ft_split(pipes[i], ' ');
	args = remove_quotes(args);
	child_1(end, i, mypath, args);
	free(args);
	while (++i < n_pipes - 1)
	{
		args = ft_split(pipes[i], ' ');
		args = remove_quotes(args);
		child_mid(end, i, mypath, args);
		free(args);
	}
	args = ft_split(pipes[i], ' ');
	args = remove_quotes(args);
	child_last(end, i, mypath, args);
	free(args);
	i = -1;
	while (++i < n_pipes)
		waitpid(-1, NULL, 0);
}
