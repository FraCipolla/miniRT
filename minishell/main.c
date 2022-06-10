/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 19:08:41 by mcipolla          #+#    #+#             */
/*   Updated: 2022/06/10 13:09:13 by mcipolla         ###   ########.fr       */
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
				execve(tmp[0], tmp, environ);
			printf("zsh: no such file or directory: %s\n", str);
			exit (0);
		}
		i++;
	}
	return (-1);
}

void	my_exec(char *str, char **mypath, char **environ)
{
	char	*cmd;
	char	**tmp;
	int		i;
	int		fd;

	i = 0;
	tmp = ft_split(str, ' ');
	while (tmp[++i])
		if (strcmp(tmp[i], "echo") == 0)
			my_echo(tmp);
	if (check_redir(tmp) == 0)
	{
		i = 0;
		while (tmp[i] && strcmp(tmp[i], ">") != 0)
			i++;
		fd = open(tmp[i + 1], O_CREAT | O_RDWR, 0644);
		tmp = cpy_matrix(tmp, 2);
		dup2(fd, 1);
	}
	if (check_dot(str, environ) == -1)
	{
		while (*mypath)
		{
			cmd = ft_strjoin(*mypath, tmp[0]);
			if (access(cmd, R_OK) == 0)
			{
				execve(cmd, tmp, environ);
			}
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

	pid = fork();
	if (pid > 0)
	{
		waitpid(-1, NULL, 0);
		return (0);
	}
	if (pid == 0)
	{
		my_exec(str, mypath, environ);
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
	else if (strncmp(str, "env", 3) == 0)
		return (my_env(str));
	else if (strncmp(str, "export", 6) == 0)
		return (my_exp(str));
	else if (strncmp(str, "unset", 5) == 0)
		return (my_unset(str + 5));
	else if (check_command(str, mypath) == 0)
		return (0);
	return (-1);
}

void	handler(int	sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		printf("CIAO");
	}
}

// struct sigaction	sig_init(struct sigaction *sa)
// {
// 	sigemptyset(&sa->sa_mask);
// 	sa->sa_sigaction = new_signal;
// 	sa->sa_flags = SA_SIGINFO;
// 	sigaddset(&sa->sa_mask, SIGINT);
	
// 	return (*sa);
// }

int main()
{
	char	*buff;
	char	**mypath;
	int		i;

	signal(SIGINT, handler);
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
