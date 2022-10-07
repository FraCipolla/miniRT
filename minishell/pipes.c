/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 17:51:30 by mcipolla          #+#    #+#             */
/*   Updated: 2022/10/07 16:13:20 by mcipolla         ###   ########.fr       */
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
	return (ret);
}

void	do_pipe(int stdout_cpy, char **cmd,char **envp)
{
	int		end[2];
	int		pid;
	char	**mypath;

	pipe(end);
	mypath = get_path();
	pid = fork();
	if (pid == 0)
	{
		close(end[0]);
		if (stdout_cpy != 0)
			dup2(stdout_cpy, STDOUT_FILENO);
		else
			dup2(end[1], STDOUT_FILENO);
		split_exec(mypath, cmd, envp);
		exit(0);
	}
	close(end[1]);
	dup2(end[0], STDIN_FILENO);
	close(end[0]);
	my_free(mypath);
}

void	pipex(char **pipes, int n_pipes, char **envp)
{
	int		i;
	char	**args;
	int		std_cpy[2];

	i = -1;
	set_fd(&std_cpy[0], &std_cpy[1], 0);
	while (++i <= n_pipes)
	{
		args = ft_split(pipes[i], ' ');
		if (i == n_pipes)
			do_pipe(std_cpy[1], args, envp);
		else
			do_pipe(0, args, envp);
		my_free(args);
	}
	i = -1;
	while (++i <= n_pipes)
		waitpid(-1, NULL, 0);
	dup2(std_cpy[0], STDIN_FILENO);
	set_fd(&std_cpy[0], &std_cpy[1], 1);
	set_fd(&std_cpy[0], &std_cpy[1], 2);
}
