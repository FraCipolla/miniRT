/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 19:08:41 by mcipolla          #+#    #+#             */
/*   Updated: 2022/09/24 20:27:38 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_exec(char **mypath, char **environ, char **cmd)
{
	char	*tmp;
	int		pid;
	int		status;

	check_redir(cmd);
	cmd = cut_red(cmd);
	pid = fork();
	if (pid == 0)
	{
		if (check_dot(cmd, environ) == -1)
		{
			while (*mypath)
			{
				tmp = ft_strjoin(*mypath, cmd[0]);
				if (access(tmp, R_OK) == 0)
					execve(tmp, cmd, environ);
				mypath++;
				free(tmp);
			}
			printf("bash: %s: command not found\n", cmd[0]);
		}
		exit(127);
	}
	else
	{
		waitpid(pid, &status, 0);
		set_global(status);
	}
}

void	set_fd(int *stdin_cpy, int *stdout_cpy, int flag)
{
	if (flag == 0)
	{
		*stdin_cpy = dup(0);
		*stdout_cpy = dup(1);
	}
	else
	{
		dup2(*stdin_cpy, 0);
		dup2(*stdout_cpy, 1);
	}
}

void	split_exec(char **mypath, char **cmd)
{
	extern char	**environ;
	int	stdout_cpy;
	int	stdin_cpy;

	set_fd(&stdin_cpy, &stdout_cpy, 0);
	if (getenv("PATH") == NULL)
		while (*mypath)
			*mypath++ = NULL;
	if (check_builtin(cmd[0]) == 0)
		exec_builtin(cmd);
	else
		my_exec(mypath, environ, cmd);
	set_fd(&stdin_cpy, &stdout_cpy, 1);
}

void	check_pipes(char *str, char **mypath, char **args)
{
	char	**pipes;
	int		matrix_size;
	int		**end;
	int		n_pipes;

	end = NULL;
	matrix_size = 0;
	pipes = ft_split(str, '|');
	while (pipes[matrix_size])
		matrix_size++;
	n_pipes = matrix_size - 1;
	if (matrix_size > 1)
	{
		end = (int **)malloc(sizeof(int *) * matrix_size - 1);
		matrix_size = -1;
		while (++matrix_size < n_pipes)
		{
			end[matrix_size] = malloc(sizeof(int) * 2);
			pipe(end[matrix_size]);
		}
	}
	if(end)
		pipex(end, pipes, n_pipes);
	else
		split_exec(mypath, args);
}

char	**init()
{
	int		i;
	char	**mypath;

	clt_echo("-ctlecho");
	mypath = ft_split(getenv("PATH"), ':');
	i = -1;
	while (mypath[++i])
		mypath[i] = ft_strjoin(mypath[i], "/");
	signal(SIGINT, action);
	signal(SIGQUIT, SIG_IGN);
	return (mypath);
}

char	*first_check(char *buff)
{
	if (buff == NULL)
		msg_exit();
	add_history(buff);
	buff = check_empty_logical(buff);
	buff = ft_addspaces(buff);
	if (buff == NULL)
	{
		buff = ft_strdup("");
		g_exit = 258;
	}
	return (buff);
}

int	main(void)
{
	char	*buff;
	char	**mypath;
	char	**args;

	mypath = init();
	while (1)
	{
		buff = readline("minishell: ");
		buff = first_check(buff);
		if (buff[0] != '\0')
		{
			args = ft_split(buff, ' ');
			if (logical_operator(buff, mypath, NULL) == 1)
				check_pipes(buff, mypath, remove_quotes(args));
		}
		free(buff);
	}
	last_free(mypath, args, buff);
	return (0);
}
