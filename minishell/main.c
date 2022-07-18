/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 19:08:41 by mcipolla          #+#    #+#             */
/*   Updated: 2022/07/18 16:47:49 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_dot(char *str, char **environ)
{
	int		i;
	char	**tmp;

	i = 0;
	while (str[i])
	{
		if(strncmp(str + i, "./", 2) == 0)
		{
			tmp = ft_split(str, ' ');
			if (access(tmp[0], R_OK) == 0)
			{
				if (strncmp(str + i, "./minishell", 11) == 0)
					ft_increase_shlvl();
				execve(tmp[0], tmp, environ);
			}
			printf("zsh: no such file or directory: %s\n", str);
			exit (0);
		}
		i++;
	}
	return (-1);
}

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
	// char 		*tmp;

	pid = fork();
	if (pid > 0)
		waitpid(-1, NULL, 0);
	if (pid == 0)
	{
		i = -1;
		cmd = ft_split(str, ' ');
		// tmp = check_infile(cmd);
		check_redir(cmd);
		// while (cmd[++i])
		// 	if (strcmp(cmd[i], ">") == 0 || strcmp(cmd[i], ">>") == 0)
		// 	{
		// 		pid = fork();
		// 		if (pid == 0)
		// 		{
		// 			check_redir(cmd, i, tmp);
		// 			break ;
		// 		}
		// 	}
		// if (pid > 0)
		// 	exit (0);
		if (check_strcmp(str, mypath) == -1)
			printf("zsh: command not found: %s\n", cmd[0]);
	}
}

void	action(int sig)
{
	if (sig == SIGINT)
	{
		write(0, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sig_init(struct sigaction *sa)
{
	// sa->sa_sigaction = action;
	
	sigemptyset(&sa->sa_mask);
	sigdelset(&sa->sa_mask, SIGINT);
	signal(SIGINT, action);
	signal(SIGQUIT, SIG_IGN);
}

int main()
{
	char    *buff;
	char    **mypath;
	int     i;
	struct	sigaction	sa;

	sig_init(&sa);
	mypath = ft_split(getenv("PATH"), ':');
	i = -1;
	while (mypath[++i])
		mypath[i] = ft_strjoin(mypath[i], "/");
	while (1)
	{
		buff = readline("minishell: ");
		if (ft_strcmp(rl_line_buffer, "^C") == 0)
			printf("ENTRA");
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
				break ;
			}
			else
				make_fork(buff, mypath);
		}
	}
	// my_free(mypath);
	return (0);
}
