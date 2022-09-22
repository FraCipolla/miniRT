/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 19:08:41 by mcipolla          #+#    #+#             */
/*   Updated: 2022/09/21 16:31:55 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_exec(char **mypath, char **environ, char **cmd)
{
	char	*tmp;

	check_redir(cmd);
	cmd = cut_red(cmd);
	exit_value = 0;
	if (check_dot(cmd, environ) == -1)
	{
		while (*mypath)
		{
			tmp = ft_strjoin(*mypath, cmd[0]);
			if (access(tmp, R_OK) == 0)
			{
				// if (ft_strcmp(cmd[0], "cat") == 0)
				// 	clt_echo("ctlecho");
				execve(tmp, cmd, environ);
			}
			mypath++;
		}
		exit_value = 127;
		printf("bash: %s: command not found\n", cmd[0]);
	}
	exit(0);
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
	int	pid;
	int	stdout_cpy;
	int	stdin_cpy;

	set_fd(&stdin_cpy, &stdout_cpy, 0);
	if (getenv("PATH") == NULL)
		while (*mypath)
			*mypath++ = NULL;
	if (check_builtin(cmd[0]) == 0)
		exec_builtin(cmd);
	else
	{
		pid = fork();
		if (pid == 0)
			my_exec(mypath, environ, cmd);
		else
			waitpid(pid, NULL, 0);
	}
	// clt_echo("-ctlecho");
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

	// clt_echo("-ctlecho");
	mypath = ft_split(getenv("PATH"), ':');
	i = -1;
	while (mypath[++i])
		mypath[i] = ft_strjoin(mypath[i], "/");
	signal(SIGINT, action);
	signal(SIGQUIT, SIG_IGN);
	return (mypath);
}

void	first_check(char **buff)
{
	if (*buff == NULL)
		msg_exit();
	add_history(*buff);
	*buff = ft_addspaces(*buff);
	if (*buff == NULL)
	{
		*buff = ft_strdup("");
		exit_value = (258);
	}
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
		first_check(&buff);
		if (buff[0] != '\0')
		{
			args = ft_split(buff, ' ');
			if (strncmp(args[0], "exit", 4) == 0)
			{
				write(1, "exit\n", 5);
				break ;
			}
			else
				check_pipes(buff, mypath, remove_quotes(args));
		}
		free(buff);
		// clt_echo("-ctlecho");
	}
	last_free(mypath, args, buff);
	return (0);
}
