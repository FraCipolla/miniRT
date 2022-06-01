/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 19:08:41 by mcipolla          #+#    #+#             */
/*   Updated: 2022/06/01 22:20:34 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*command_path(char **envp)
{
	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
			return (*envp + 5);
		envp++;
	}
	return (NULL);
}

int	check_command(char *str, char **mypath)
{
	char	**tmp;
	char	*cmd;
	extern char **environ;

	tmp = ft_split(str, ' ');
	while (*mypath)
	{
		cmd = ft_strjoin(*mypath, tmp[0]);
		if (access(cmd, R_OK) == 0)
			execve(cmd, tmp, environ);
		mypath++;
	}
	return (-1);
}

int	check_strcmp(char *str, char **mypath)
{
	char	path[1000];
	if (strcmp(str, "pwd") == 0)
	{
		getcwd(path, 100);
		printf("%s\n", path);
		return (0);
	}
	if (strncmp(str, "cd", 2) == 0)
	{
		if (str[2] == ' ' && chdir(str + 3) == -1)
			printf("cd: no such file or directory: %s\n", str + 3);
		return (0);
	}
	if (check_command(str, mypath) == 0)
		return (0);
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
		buff = readline(CGREEN "minishell: " RESET);
		if (strcmp(buff, "exit") == 0)
			break ;
		if (buff != NULL)
			add_history(buff);
		if (check_strcmp(buff, mypath) == -1)
			printf("zsh: command not found: %s\n", buff);
		free(buff);
	}
	return (0);
}