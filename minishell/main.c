/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 19:08:41 by mcipolla          #+#    #+#             */
/*   Updated: 2022/06/03 16:01:45 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	make_echo(char **str)
{
	int		fd;
	char	*cmd;
	int		i;

	i = 1;
	cmd = NULL;
	while (strncmp(str[i], ">", 1) != 0)
	{
		cmd = ft_strjoin(cmd, str[i]);
		cmd = ft_strjoin(cmd, " ");
		i++;
	}
	i++;
	fd = open(str[i], O_CREAT | O_RDWR | O_TRUNC, 0644);
	write(fd, cmd, strlen(cmd));
	exit (0);
}

int	check_command(char *str, char **mypath)
{
	char		**tmp;
	char		*cmd;
	extern char **environ;
	pid_t		pid;

	pid = fork();
	if (pid > 0)
	{
		waitpid(-1, NULL, 0);
		return (0);
	}
	tmp = ft_split(str, ' ');
	if (pid == 0)
	{
		while (*mypath)
		{
			cmd = ft_strjoin(*mypath, tmp[0]);
			if (access(cmd, R_OK) == 0)
			{
				if (strcmp(tmp[0], "echo") == 0)
					make_echo(tmp);
				execve(cmd, tmp, environ);
			}
			mypath++;
		}
		printf("zsh: command not found: %s\n", str);
		exit(0);
	}
	return (-1);
}

int	check_pwd(char *str)
{
	int	i;

	i = 3;
	while (str[i])
	{
		if (str[i] != ' ')
		{
			printf("pwd: too many arguments\n");
			return (-1);
		}
		i++;
	}
	return (0);
}

int	check_strcmp(char *str, char **mypath)
{
	char	path[1000];
	
	if (strncmp(str, "pwd", 3) == 0)
	{
		if (check_pwd(str) == 0)
		{
			getcwd(path, 1000);
			printf("%s\n", path);
			return (0);
		}
		else
			return (0);
	}
	else if (strncmp(str, "cd", 2) == 0)
	{
		if (str[2] == ' ' && chdir(str + 3) == -1)
			printf("cd: no such file or directory: %s\n", str + 3);
		return (0);
	}
	else if (check_command(str, mypath) == 0)
	{
		if (strncmp(str, "cat", 3) == 0)
			write(1, "%\n", 2);
		return (0);
	}
	return (-1);
}

int main()
{
	char	*buff;
	char	**mypath;
	int		i;

	mypath = ft_split(getenv("PATH"), ':');
	i = -1;
	while (mypath[++i])
		mypath[i] = ft_strjoin(mypath[i], "/");
	while (1)
	{
		buff = readline("minishell: ");
		if (strcmp(buff, "exit") == 0)
			break ;
		if (buff != NULL && strncmp(buff, "\0", 1) != 0)
			add_history(buff);
		if (check_strcmp(buff, mypath) == -1)
			printf("zsh: command not found: %s\n", buff);
		free(buff);
	}
	return (0);
}
