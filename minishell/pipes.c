/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 17:51:30 by mcipolla          #+#    #+#             */
/*   Updated: 2022/10/04 15:04:03 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_pipe(int stdcpy, char **cmd, char **envp)
{
	char	**mypath;
	int		heredoc;
	int		end[2];
	int		pid;

	mypath = NULL;
	pipe(end);
	pid = fork();
	mypath = get_path();
	heredoc = here_doc_pipes(cmd);
	if (pid == 0)
	{
		close(end[0]);
		if (heredoc != -1)
		{
			cmd = cut_heredoc(cmd);
			dup2(heredoc, STDIN_FILENO);
		}
		if (stdcpy != 0)
		{
			close(end[1]);
			dup2(stdcpy, STDOUT_FILENO);
		}
		else
			dup2(end[1], STDOUT_FILENO);
		close(end[1]);
		split_exec(mypath, cmd, envp);
		exit(0);
	}
	if (pid > 0)
	{
		// waitpid(pid, 0, 0);
		dup2(end[0], 0);
		close(end[0]);
		close(end[1]);
	}
}

void	pipex2(char **pipes, int n_pipes, char **envp)
{
	int		i;
	char	**args;
	// int		end[n_pipes * 2];
	int		stdin_cpy;
	int		stdout_cpy;

	i = -1;
	stdout_cpy = dup(1);
	stdin_cpy = dup(0);
	int	*pid = malloc(sizeof(int) * n_pipes + 1);
	while (++i <= n_pipes)
	{
		args = ft_split(pipes[i], ' ');
		if (i == n_pipes)
			do_pipe(stdout_cpy, args, envp);
		else
			do_pipe(0, args, envp);
		free(args);
	}
	dup2(stdin_cpy, 0);
	close(stdin_cpy);
	close(stdout_cpy);
	i = -1;
	while (pid[++i] <= n_pipes)
		waitpid(pid[i], NULL, 0);
}
