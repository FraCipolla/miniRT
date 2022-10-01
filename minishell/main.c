/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 19:08:41 by mcipolla          #+#    #+#             */
/*   Updated: 2022/10/01 15:05:38 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**cmd_path(char **args)
{
	int		i;
	char	*tmp;

	if (args[0][0] == '/')
	{
		i = ft_strlen(args[0]);
		while (args[0][i] != '/')
			i--;
		tmp = ft_strdup(args[0] + i);
		free(args[0]);
		args[0] = tmp;
	}
	return (args);
}

void	my_exec(char **mypath, char **environ, char **cmd)
{
	char	*tmp;
	int		pid;
	int		status;

	check_redir(cmd);
	cmd = cut_red(cmd);
	if (cmd[0] == NULL)
		return ;
	cmd = cmd_path(cmd);
	pid = fork();
	signal(SIGINT, action_in_process);
	// clt_echo("ctlecho");
	if (pid == 0)
	{
		if (check_dot(cmd, environ) == -1)
		{
			while (mypath && *mypath)
			{
				tmp = ft_strjoin(*mypath, cmd[0]);
				if (access(tmp, R_OK) == 0)
					execve(tmp, cmd, environ);
				mypath++;
				free(tmp);
			}
			printf("%s: command not found\n", cmd[0]);
		}
		exit(127);
	}
	else
	{
		waitpid(pid, &status, 0);
		set_global(status);
		my_free(cmd);
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

	if (between_parentheses(cmd[0]) == 0)
	{
		exec_subshell(cmd);
		return ;
	}
	set_fd(&stdin_cpy, &stdout_cpy, 0);
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
	my_free(pipes);
}

char	**init()
{
	int		i;
	char	**mypath;
	char	*tmp;

	// clt_echo("-ctlecho");
	if (getenv("PATH") == NULL)
		mypath = NULL;
	else
	{
		tmp = getenv("PATH");
		mypath = ft_split(tmp, ':');
		i = -1;
		while (mypath[++i])
			mypath[i] = ft_strjoin(mypath[i], "/");
	}
	signal(SIGINT, action);
	signal(SIGQUIT, SIG_IGN);
	return (mypath);
}

char	*first_check(char *buff)
{
	char	*tmp;

	if (buff[0] == '\0')
		return(buff);
	tmp = buff;
	if (buff == NULL)
		msg_exit();
	buff = check_empty_parentheses(buff);
	if (buff == NULL)
		add_history(tmp);
	else
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

void	start_parsing(char *buff, char **mypath)
{
	char	**args;
	char	**args2;
	int		i;

	args = ft_split(buff, ';');
	i = 0;
	while (args[i])
	{
		args2 = ft_split(args[i], ' ');
		if (args2 == NULL)
			return ;
		if (logical_operator(args[i], mypath, NULL) == 1)
			check_pipes(args[i], mypath, remove_quotes(args2));
		my_free(args2);
		i++;
	}
	my_free(args);
}

int	main(int argc, char *argv[])
{
	char	*buff;
	char	**mypath;

	while (1)
	{
		mypath = init();
		if (argc > 1)
			buff = argv[1];
		else
		{
			buff = readline("minishell: ");
			buff = first_check(buff);
		}
		if (buff[0] != '\0')
			start_parsing(buff, mypath);
		if (argc > 1)
			exit(0);
		free(buff);
		my_free(mypath);
	}
	return (0);
}
