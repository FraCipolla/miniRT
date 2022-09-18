/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 19:08:41 by mcipolla          #+#    #+#             */
/*   Updated: 2022/09/07 14:29:01 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_exec(char **mypath, char **environ, char **cmd)
{
	char	*tmp;

	cmd = cut_red(cmd);
	if (check_dot(cmd, environ) == -1)
	{
		while (*mypath)
		{
			tmp = ft_strjoin(*mypath, cmd[0]);
			if (access(tmp, R_OK) == 0)
			{
				// if (ft_strcmp(cmd[0], "cat") == 0)
				// {
				// 	if (fork() == 0)
				// 		clt_echo("ctlecho");
				// 	else
				// 		waitpid(-1, NULL, 0);
				// }
				execve(tmp, cmd, environ);
			}
			mypath++;
		}
		exit_value = 127;
		printf("bash: %s: command not found\n", cmd[0]);
	}
	exit(0);
}

int	check_builtin(char *str)
{
	if (strcmp(str, "export") == 0
		|| strcmp(str, "cd") == 0
		|| strcmp(str, "unset") == 0
		|| strcmp(str, "echo") == 0
		|| strcmp(str, "env") == 0
		|| strcmp(str, "pwd") == 0
		|| strcmp(str, "exit") == 0)
		return (0);
	return (1);
}

void	exec_builtin(char **cmd)
{
	int	fd;

	fd = check_redir(cmd);
	cmd = cut_red(cmd);
	// signal(SIGINT, SIG_DFL);
	// signal(SIGQUIT, SIG_DFL);
	// signal(SIGINT, SIG_IGN);
	// signal(SIGQUIT, SIG_IGN);
	// signal(SIGINT, action);
	if (strcmp(cmd[0], "cd") == 0)
		exit_value = my_cd(cmd);
	else if (strcmp(cmd[0], "export") == 0)
		exit_value = my_exp(cmd);
	else if (strcmp(cmd[0], "unset") == 0)
		exit_value = my_unset(cmd[1]);
	else if (strcmp(cmd[0], "echo") == 0)
		exit_value = my_echo(cmd, fd);
	else if (strncmp(cmd[0], "pwd", 3) == 0)
		exit_value = my_pwd(cmd);
	else if (strcmp(cmd[0], "env") == 0)
		exit_value = my_env(cmd);
	else
		printf("bash: %s: command not found\n", cmd[0]);
}

void	split_exec(char **mypath, char **cmd)
{
	extern char	**environ;
	int	pid;
	int	stdout_cpy;
	int	stdin_cpy;

	stdin_cpy = dup(0);
	stdout_cpy = dup(1);
	check_redir(cmd);
	if (getenv("PATH") == NULL)
		while (*mypath)
		{
			*mypath = NULL;
			mypath++;
		}
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
	dup2(stdin_cpy, 0);
	dup2(stdout_cpy, 1);
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

int	main(void)
{
	char	*buff;
	char	**mypath;
	char	**args;

	mypath = init();
	while (1)
	{
		buff = readline("minishell: ");
		if (buff == NULL)
			msg_exit("logout\n");
		if (buff[0] != '\0')
		{
			add_history(buff);
			buff = ft_addspaces(buff);
			if (buff == NULL)
				exit_value = (258);
			else
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
		}
	}
	free(buff);
	// my_free(mypath);
	return (0);
}
