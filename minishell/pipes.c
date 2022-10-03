/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 17:51:30 by mcipolla          #+#    #+#             */
/*   Updated: 2022/10/03 14:47:39 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_pipe(int stdcpy, int pid, char **cmd, char **envp)
{
	char	**mypath = NULL;
	int		heredoc;
	int		end[2];

	pipe(end);
	pid = fork();
	mypath = get_path();
	heredoc = here_doc_pipes(cmd);
	// close(end[i][0]);
	if (pid == 0)
	{
		close(end[0]);
		if (heredoc != -1)
		{
			cmd = cut_heredoc(cmd);
			dup2(heredoc, STDIN_FILENO);
		}
		if (stdcpy)
			dup2(stdcpy, STDOUT_FILENO);
		else
			dup2(end[1], STDOUT_FILENO);
		close(end[1]);
		split_exec(mypath, cmd, envp);
		exit(0);
	}
	// close(end[1]);
	close(end[0]);
}

void	pipex2(int **end, char **pipes, int n_pipes, char **envp)
{
	int		i;
	char	**args;
	int		*pid;
	int		stdout_cpy;

	i = -1;
	end = NULL;
	stdout_cpy = dup(1);
	pid = malloc(sizeof(int) * n_pipes + 1);
	while (++i <= n_pipes)
	{
		args = ft_split(pipes[i], ' ');
		if (i == n_pipes)
			do_pipe(stdout_cpy, pid[i], args, envp);
		else
			do_pipe(0, pid[i], args, envp);
		free(args);
	}
	i = -1;
	while (pid[++i] <= n_pipes)
		waitpid(pid[i], NULL, 0);
	free(pid);
}