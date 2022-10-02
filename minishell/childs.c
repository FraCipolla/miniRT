/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 17:51:30 by mcipolla          #+#    #+#             */
/*   Updated: 2022/10/02 20:33:47 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	**cut_heredoc(char **args)
// {
// 	int		i;
// 	int		n;
// 	char	**ret;

// 	i = -1;
// 	n = 0;
// 	while (args[++i])
// 	{
// 		if (strcmp(args[i], "<<") == 0)
// 			n += 2;
// 	}
// 	ret = malloc(sizeof(char *) * i - (n) + 1);
// 	i = 0;
// 	n = 0;
// 	while (args[i])
// 	{
// 		if (strcmp(args[i], "<<") == 0)
// 			i += 2;
// 		else
// 		{
// 			ret[n] = ft_strdup(args[i]);
// 			n++;
// 			i++;
// 		}
// 	}
// 	ret[n] = NULL;
// 	my_free(args);
// 	return (ret);
// }

void	child_1(int **end, int i, char **cmd, int pid)
{
	char	**mypath = NULL;
	int		heredoc;
	extern char	**environ;

	mypath = get_path(mypath);
	heredoc = here_doc_pipes(cmd);
	pid = fork();
	if (pid == 0)
	{
		close(end[i][0]);
		if (heredoc != -1)
		{
			cmd = cut_heredoc(cmd);
			dup2(heredoc, STDIN_FILENO);
		}
		dup2(end[i][1], STDOUT_FILENO);
		close(end[i][1]);
		split_exec(mypath, cmd, environ);
		exit(0);
	}
	my_free(mypath);
	close(end[i][1]);
}

void	child_mid(int **end, int i, char **cmd, int pid)
{
	char	**mypath = NULL;
	int		heredoc;
	extern char	**environ;
	
	mypath = get_path(mypath);
	heredoc = here_doc_pipes(cmd);
	pid = fork();
	if (pid == 0)
	{
		close(end[i][0]);
		if (heredoc != -1)
		{
			cmd = cut_heredoc(cmd);
			dup2(heredoc, STDIN_FILENO);
		}
		// dup2(end[i - 1][0], STDIN_FILENO);
		dup2(end[i][1], STDOUT_FILENO);
		close(end[i - 1][0]);
		close(end[i][1]);
		split_exec(mypath, cmd, environ);
		exit(0);
	}
	my_free(mypath);
	close(end[i][1]);
	close(end[i - 1][0]);
}

void	child_last(int **end, int i, char **cmd, int pid)
{
	int		stdout_cpy;
	char	**mypath = NULL;
	int		heredoc;
	extern char	**environ;

	mypath = get_path(mypath);
	stdout_cpy = dup(1);
	heredoc = here_doc_pipes(cmd);
	pid = fork();
	if (pid == 0)
	{
		close(end[i -1][1]);
		if (heredoc != -1)
		{
			cmd = cut_heredoc(cmd);
			dup2(heredoc, STDIN_FILENO);
		}
		dup2(end[i - 1][0], STDIN_FILENO);
		dup2(stdout_cpy, STDOUT_FILENO);
		close(end[i - 1][0]);
		split_exec(mypath, cmd, environ);
		exit(0);
	}
	my_free(mypath);
	close(end[i - 1][0]);
}

void	pipex(int **end, char **pipes, int n_pipes)
{
	int		i;
	char	**args;
	int		*pid;
	int		stdcpy;

	i = 0;
	stdcpy = dup(1);
	pid = malloc(sizeof(int) * n_pipes + 1);
	args = ft_split(pipes[i], ' ');
	child_1(end, i, args, pid[i]);
	free(args);
	while (++i < n_pipes)
	{
		args = ft_split(pipes[i], ' ');
		child_mid(end, i, args, pid[i]);
		free(args);
	}
	args = ft_split(pipes[i], ' ');
	child_last(end, i, args, pid[i]);
	free(args);
	i = -1;
	while (pid[++i] <= n_pipes)
		waitpid(pid[i], NULL, 0);
	free(pid);
}
