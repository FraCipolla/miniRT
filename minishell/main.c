/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 19:08:41 by mcipolla          #+#    #+#             */
/*   Updated: 2022/06/16 17:30:52 by mcipolla         ###   ########.fr       */
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
	int		i;
	
	if (check_redir(tmp) == 0)
		tmp = cpy_matrix(tmp, 2);
	i = -1;
	while (tmp[++i])
	{
		if (strcmp(tmp[i], "env") == 0)
			my_env(tmp);
		if (strcmp(tmp[i], "echo") == 0)
			my_echo(tmp);
	}
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

int	check_command(char *str, char **mypath)
{
	extern char	**environ;
	pid_t		pid;
	char		**tmp;

	pid = fork();
	tmp = ft_split(str, ' ');
	if (pid > 0)
	{
		waitpid(-1, NULL, 0);
		return (0);
	}
	if (pid == 0)
	{
		my_exec(str, mypath, environ, tmp);
		exit(0);
	}
	return (-1);
}

int	check_strcmp(char *str, char **mypath)
{
	int	i;

	i = -1;
	if (getenv("PATH") == NULL)
		while (mypath[++i])
			mypath[i] = NULL;
	if (strncmp(str, "pwd", 3) == 0)
		return(my_pwd(str));
	else if (strncmp(str, "cd", 2) == 0)
		return (my_cd(str));
	// else if (strncmp(str, "env", 3) == 0)
	// 	return (my_env(str));
	else if (strncmp(str, "unset", 6) == 0)
		my_unset(str + 5);
	else if (strncmp(str, "export", 6) == 0)
		return (my_exp(str));
	else if (strncmp(str, "unset", 5) == 0)
		return (my_unset(str + 5));
	else if (check_command(str, mypath) == 0)
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
		buff = readline("minishell: ");
		if (buff != NULL && strncmp(buff, "\0", 1) != 0)
			add_history(buff);
		if (check_quotes(buff, 0) > 0)
			buff = quotes_resolve(buff, check_quotes(buff, 0));
		buff = rem_char(buff, 92);
		if (strncmp(buff, "exit", 4) == 0 && (buff[4] == ' ' || buff[4] == '\0'))
			break ;
		if (check_semicolon(buff, mypath) == -1)
				if (check_strcmp(buff, mypath) == -1)
					printf("zsh: command not found: %s\n", buff);
		free(buff);
	}
	return (0);
}
