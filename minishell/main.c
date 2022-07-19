/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 19:08:41 by mcipolla          #+#    #+#             */
/*   Updated: 2022/07/19 18:37:56 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_exec(char *str, char **mypath, char **environ, char **tmp)
{
	char	*cmd;
	
	tmp = cut_red(tmp);
	if (check_dot(str, environ) == -1)
	{
		while (*mypath)
		{
			cmd = ft_strjoin(*mypath, tmp[0]);
			if (access(cmd, R_OK) == 0)
				execve(cmd, tmp, environ);
			mypath++;
		}
		printf("zsh: command not found: %s\n", tmp[0]);
	}
	exit(0);
}

int	check_strcmp(char *str, char **mypath)
{
	int			i;
	char		**cmd;
	extern char	**environ;

	i = -1;
	cmd = ft_split(str, ' ');
	if (getenv("PATH") == NULL)
		while (mypath[++i])
			mypath[i] = NULL;
	if (strncmp(cmd[0], "pwd", 3) == 0)
		return(my_pwd(cmd));
	if (strcmp(cmd[0], "env") == 0)
		my_env(cmd);
	else if (strcmp(cmd[0], "cd") == 0)
		return (my_cd(str));
	else if (strcmp(cmd[0], "echo") == 0)
		return (my_echo(cmd, str));
	else if (strcmp(cmd[0], "export") == 0)
		return (my_exp(str));
	else if (strcmp(cmd[0], "unset") == 0)
		return (my_unset(cmd[1]));
	else
		my_exec(str, mypath, environ, cmd);
	return (-1);
}

void	make_fork(char *str, char **mypath)
{
	int			pid;
	int			i;
	char		**cmd;

	pid = fork();
	if (pid > 0)
		waitpid(-1, NULL, 0);
	if (pid == 0)
	{
		i = -1;
		cmd = ft_split(str, ' ');
		check_redir(cmd);
		if (check_strcmp(str, mypath) == -1)
			printf("zsh: command not found: %s\n", cmd[0]);
		exit(0);
	}
}

void	action(int sig)
{
	write(0, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	signal(sig, action);
}

char	**init(char **mypath)
{
	int	i;
	int	pid;
	extern char	**environ;
	char	**stty;

	stty = malloc(sizeof(char *) * 3);
	stty[0] = ft_strdup("stty");
	stty[1] = ft_strdup("-ctlecho");
	stty[2] = NULL;
	pid = fork();
	if (pid == 0)
		execve("/bin/stty", stty, environ);
	if (pid > 0)
	{
		waitpid(-1, NULL, 0);
		mypath = ft_split(getenv("PATH"), ':');
		i = -1;
		while (mypath[++i])
			mypath[i] = ft_strjoin(mypath[i], "/");
		signal(SIGINT, action);
		signal(SIGQUIT, SIG_IGN);
	}
	return(mypath);
}

int main()
{
	char    *buff;
	char    **mypath;

	mypath = NULL;
	mypath = init(mypath);
	while (1)
	{
		signal(SIGINT, action);
		buff = readline("minishell: ");
		if (buff == NULL)
		{
			write(0, "logout\n", 7);
			exit(0);
		}
		if (buff[0] != '\0')
		{
			add_history(buff);
			// buff = rem_char(buff, 92);
			if (check_quotes(ft_split(buff, ' '), 0) > 0)
				buff = quotes_resolve(buff, check_quotes(ft_split(buff, ' '), 0));
			if (strncmp(buff, "exit", 4) == 0 && (buff[4] == ' ' || buff[4] == '\0'))
			{
				write(1, "exit\n", 5);
				break ;
			}
			else
				make_fork(buff, mypath);
		}
	}
	// my_free(mypath);
	return (0);
}
