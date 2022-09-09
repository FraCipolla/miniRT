/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 19:08:41 by mcipolla          #+#    #+#             */
/*   Updated: 2022/09/05 17:59:08 by mcipolla         ###   ########.fr       */
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

int	check_return(char *str)
{
	if (strcmp(str, "export") == 0
	|| strcmp(str, "cd") == 0
	|| strcmp(str, "unset") == 0)
		return(0);
	return (1);
}

int	check_strcmp(char *str, char **cmd, char **mypath)
{
	int			i;
	extern char	**environ;

	i = -1;
	if (check_return(cmd[0]) == 0)
		return (0);
	if (getenv("PATH") == NULL)
		while (mypath[++i])
			mypath[i] = NULL;
	if (strncmp(cmd[0], "pwd", 3) == 0)
		return(my_pwd(cmd));
	if (strcmp(cmd[0], "env") == 0)
		my_env(cmd);
	else if (strcmp(cmd[0], "echo") == 0)
		return (my_echo(cmd, str));
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

void	make_fork(char *str, char **mypath)
{
	int			pid;
	char		**cmd;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	cmd = ft_split(str, ' ');
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
		check_redir(cmd);
		if (check_strcmp(str, cmd, mypath) == -1)
			printf("zsh: command not found: %s\n", cmd[0]);
		exit(0);
	}
	free(cmd);
}

char	**init(char **mypath)
{
	int			i;
	int			pid;
	extern char	**environ;
	char		**stty;

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
		buff = readline("minishell: ");
		if (buff == NULL)
			msg_exit("logout\n");
		if (buff[0] != '\0')
		{
			add_history(buff);
			// buff = first_check(buff);
			// if (check_quotes(ft_split(buff, ' '), 0) > 0)
			// 	buff = quotes_resolve(buff, check_quotes(ft_split(buff, ' '), 0));
			if (strncmp(buff, "exit", 4) == 0 && (buff[4] == ' ' || buff[4] == '\0'))
			{
				write(1, "exit\n", 5);
				free(buff);
				break ;
			}
			else
			{
				make_fork(buff, mypath);
				free(buff);
			}
		}
	}
	// my_free(mypath);
	return (0);
}
