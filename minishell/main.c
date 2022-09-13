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

void	my_exec(char *str, char **mypath, char **environ, char **tmp)
{
	char	*cmd;

	tmp = cut_red(tmp, 0);
	if (check_dot(str, environ) == -1)
	{
		while (*mypath)
		{
			cmd = ft_strjoin(*mypath, tmp[0]);
			if (access(cmd, R_OK) == 0)
			{
				if (ft_strcmp(tmp[0], "cat") == 0)
				{
					if (fork() == 0)
						clt_echo("ctlecho");
					else
						waitpid(-1, NULL, 0);
				}
				execve(cmd, tmp, environ);
			}
			mypath++;
		}
		printf("zsh2: command not found: %s\n", tmp[1]);
	}
	exit(0);
}

int	check_return(char *str)
{
	if (strcmp(str, "export") == 0
		|| strcmp(str, "cd") == 0
		|| strcmp(str, "unset") == 0)
		return (0);
	return (1);
}

int	check_strcmp(char *str, char **cmd, char **mypath, int fd)
{
	int			i;
	extern char	**environ;

	i = -1;
	cmd = cut_red(cmd, 0);
	if (check_return(cmd[0]) == 0)
		return (0);
	if (getenv("PATH") == NULL)
		while (mypath[++i])
			mypath[i] = NULL;
	if (strncmp(cmd[0], "pwd", 3) == 0)
		return (my_pwd(cmd));
	if (strcmp(cmd[0], "env") == 0)
		my_env(cmd);
	else if (strcmp(cmd[0], "echo") == 0)
		return (my_echo(cmd, str, fd));
	else
		my_exec(str, mypath, environ, cmd);
	return (-1);
}

void	action(int sig)
{
	write(0, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	signal(sig, action);
}

void	make_fork(char *str, char **mypath, char **cmd)
{
	int			pid;

	cut_red(cmd, 0);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	pid = fork();
	if (pid > 0)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		waitpid(-1, NULL, 0);
		signal(SIGINT, action);
		if (strcmp(cmd[0], "cd") == 0)
			my_cd(str);
		else if (strcmp(cmd[0], "export") == 0)
			my_exp(str);
		else if (strcmp(cmd[0], "unset") == 0)
			my_unset(str + 5);
	}
	if (pid == 0)
	{
		if (check_strcmp(str, cmd, mypath, check_redir(cmd)) == -1)
			printf("zsh: command not found: %s\n", cmd[0]);
		exit(0);
	}
	// free(cmd);
}

char	**init(char **mypath)
{
	int			i;

	clt_echo("-ctlecho");
	// waitpid(-1, NULL, 0);
	mypath = ft_split(getenv("PATH"), ':');
	i = -1;
	while (mypath[++i])
		mypath[i] = ft_strjoin(mypath[i], "/");
	signal(SIGINT, action);
	signal(SIGQUIT, SIG_IGN);
	return (mypath);
}

void	initialize_fork(char *str, char **mypath)
{
	char	**args;
	char	**pipes;
	int		matrix_size;

	matrix_size = 0;
	pipes = ft_split(str, '|');
	while (pipes[matrix_size])
		matrix_size++;
	while (*pipes)
	{
		args = ft_split(*pipes, ' ');
		args = remove_quotes(args);
		make_fork(*pipes, mypath, args);
		pipes++;
		free(args);
	}
}

int	main(void)
{
	char	*buff;
	char	**mypath;
	char	**args;

	mypath = NULL;
	mypath = init(mypath);
	while (1)
	{
		buff = readline("minishell: ");
		if (buff == NULL)
			msg_exit("logout\n");
		if (buff[0] != '\0')
		{
			add_history(buff);
			args = ft_split(buff, ' ');
			if (strncmp(args[0], "exit", 4) == 0)
			{
				write(1, "exit\n", 5);
				free(buff);
				break ;
			}
			else
				initialize_fork(buff, mypath);
			free(buff);
		}
	}
	// my_free(mypath);
	return (0);
}
