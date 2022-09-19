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

void	child_1(int **end, int i, char **cmd, int pid)
{
	int		stdout_cpy;
	int		stdin_cpy;
	char	**mypath;

	mypath = init();
	stdin_cpy = dup(0);
	stdout_cpy = dup(1);
	pid = fork();
	if (pid == 0)
	{
		close(end[i][0]);
		// dup2(f1, STDIN_FILENO);
		dup2(end[i][1], STDOUT_FILENO);
		close(end[i][1]);
		split_exec(mypath, cmd, stdin_cpy);
		dup2(stdout_cpy, 1);
		exit(0);
	}
	else
	{
		// close(f1);
		close(end[0][1]);
	}
}

void	child_mid(int **end, int i, char **cmd, int pid)
{
	int		stdout_cpy;
	int		stdin_cpy;
	char	**mypath;

	mypath = init();
	stdout_cpy = dup(1);
	stdin_cpy = dup(0);
	pid = fork();
	if (pid == 0)
	{
		close(end[i][0]);
		dup2(end[i - 1][0], STDIN_FILENO);
		dup2(end[i][1], STDOUT_FILENO);
		close(end[i - 1][0]);
		close(end[i][1]);
		split_exec(mypath, cmd, stdin_cpy);
		dup2(stdout_cpy, 1);
		exit(0);
	}
	else
	{
		close(end[i - 1][0]);
		close(end[i][1]);
	}
}

void	child_last(int **end, int i, char **cmd, int pid)
{
	int		stdout_cpy;
	int		stdin_cpy;
	char	**mypath;

	mypath = init();
	stdin_cpy = dup(0);
	stdout_cpy = dup(1);
	pid = fork();
	if (pid == 0)
	{
		// close(end[i][0]);
		dup2(end[i - 1][0], STDIN_FILENO);
		dup2(stdout_cpy, STDOUT_FILENO);
		close(end[i - 1][0]);
		// close(end[i][1]);
		// close(f2);
		split_exec(mypath, cmd, stdin_cpy);
		dup2(stdout_cpy, 1);
		exit(0);
	}
	else
	{
		dup2(stdout_cpy, 1);
		close(end[i - 1][0]);
	}
}

void	pipex(int **end, char **pipes, int n_pipes)
{
	int	i;
	char	**args;
	int		*pid;
	int		status;

	i = 0;
	pid = malloc(sizeof(int) * n_pipes + 1);
	args = ft_split(pipes[i], ' ');
	args = remove_quotes(args);
	child_1(end, i, args, pid[i]);
	free(args);
	while (++i < n_pipes)
	{
		args = ft_split(pipes[i], ' ');
		args = remove_quotes(args);
		child_mid(end, i, args, pid[i]);
		free(args);
	}
	args = ft_split(pipes[i], ' ');
	args = remove_quotes(args);
	child_last(end, i, args, pid[i]);
	free(args);
	i = -1;
	while (pid[++i] < n_pipes)
		waitpid(pid[i], &status, 0);
}
