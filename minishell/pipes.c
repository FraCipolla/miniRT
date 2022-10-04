/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 17:51:30 by mcipolla          #+#    #+#             */
/*   Updated: 2022/10/04 15:20:25 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**cut_heredoc(char **args)
{
	int		i;
	int		n;
	char	**ret;

	i = -1;
	n = 0;
	while (args[++i])
	{
		if (strcmp(args[i], "<<") == 0)
			n += 2;
	}
	ret = malloc(sizeof(char *) * i - (n) + 1);
	i = 0;
	n = 0;
	while (args[i])
	{
		if (strcmp(args[i], "<<") == 0)
			i += 2;
		else
			ret[n++] = ft_strdup(args[i++]);
	}
	ret[n] = NULL;
	my_free(args);
	return (ret);
}

void	do_pipe(int stdcpy, char **cmd, char **mypath, char **envp)
{
	int		heredoc;
	int		end[2];
	int		pid;

	pipe(end);
	pid = fork();
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
			dup2(stdcpy, STDOUT_FILENO);
		else
			dup2(end[1], STDOUT_FILENO);
		split_exec(mypath, cmd, envp);
		exit(0);
	}
	dup2(end[0], 0);
	close(end[0]);
	close(end[1]);
}

void	pipex(char **pipes, int n_pipes, char **mypath, char **envp)
{
	int		i;
	char	**args;
	int		std_cpy[2];
	int		*pid;

	i = -1;
	std_cpy[1] = dup(1);
	std_cpy[0] = dup(0);
	pid = malloc(sizeof(int) * n_pipes + 1);
	while (++i <= n_pipes)
	{
		args = ft_split(pipes[i], ' ');
		if (i == n_pipes)
			do_pipe(std_cpy[1], args, mypath, envp);
		else
			do_pipe(0, args, mypath, envp);
		free(args);
	}
	dup2(std_cpy[0], 0);
	close(std_cpy[0]);
	close(std_cpy[1]);
	i = -1;
	while (pid[++i] <= n_pipes)
		waitpid(pid[i], NULL, 0);
}
