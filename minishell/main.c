/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 19:08:41 by mcipolla          #+#    #+#             */
/*   Updated: 2022/07/04 20:13:26 by mcipolla         ###   ########.fr       */
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

char	*infile(char **args)
{
	int		i;
	char	*ret;
	char	*buff;
	int		fd;

	i = -1;
	ret = NULL;
	while (args[++i])
	{
		if (args[i][0] == '<')
		{
			fd = open(args[i + 1], O_RDONLY, 0644);
			buff = get_next_line (fd);
			printf("buff: %s\n", buff);
			ret = ft_strjoin(ret, buff);
			close (fd);
		}
	}
	return (ret);
}

void	my_exec(char *str, char **mypath, char **environ, char **tmp)
{
	char	*cmd;
	// char	*inf;
	// int		fd;

	// inf = strdup(infile(tmp));
	// printf("INF: %s\n", inf);
	// fd = open("TMPFD", O_CREAT | O_RDWR, 0644);
	// write (fd, inf, ft_strlen(inf));
	// dup2(fd, 0);
	// if (check_redir(tmp) == -1)
	// 	exit(0);
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
		printf("zsh: command not found: %s\n", str);
	}
	exit(0);
}

int	check_strcmp(char *str, char **mypath, char **environ)
{
	int			i;
	char		**cmd;

	i = -1;
	cmd = ft_split(str, ' ');
	while (cmd[++i])
	{
		if (strcmp(cmd[i], ">") == 0)
		{
			if (fork() > 0)
				check_redir(cmd, i);
		}
	}
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
	extern char	**environ;

	pid = fork();
	if (pid > 0)
		waitpid(-1, NULL, 0);
	if (pid == 0)
	{
		// if (check_semicolon(str, mypath) == -1)
		// {
			if (check_strcmp(str, mypath, environ) == -1)
				printf("zsh: command not found: %s\n", str);
		// }
	}
}

int main()
{
	char    *buff;
	char    **mypath;
	int     i;

	mypath = ft_split(getenv("PATH"), ':');
	i = -1;
	while (mypath[++i])
		mypath[i] = ft_strjoin(mypath[i], "/");
	while (1)
	{
		buff = readline("minishell: ");
		if (buff != NULL && strncmp(buff, "\0", 1) != 0)
		{
			add_history(buff);
			buff = rem_char(buff, 92);
			if (check_quotes(ft_split(buff, ' '), 0) > 0)
				buff = quotes_resolve(buff, check_quotes(ft_split(buff, ' '), 0));
			if (strncmp(buff, "exit", 4) == 0 && (buff[4] == ' ' || buff[4] == '\0'))
			{
				free(buff);
				break ;
			}
			else
				make_fork(buff, mypath);
			free(buff);
		}
	}
	// my_free(mypath);
	return (0);
}
