/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 19:08:41 by mcipolla          #+#    #+#             */
/*   Updated: 2022/06/20 23:11:25 by mcipolla         ###   ########.fr       */
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
	char	*inf;
	int		fd;

	inf = strdup(infile(tmp));
	printf("INF: %s\n", inf);
	fd = open("TMPFD", O_CREAT | O_RDWR, 0644);
	write (fd, inf, ft_strlen(inf));
	dup2(fd, 0);
	// check_redir(tmp);
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

int	check_command(char *str, char **mypath, char **args)
{
	extern char	**environ;
	pid_t		pid;
	int			i;

	pid = fork();
	i = -1;
	if (pid > 0)
	{
		waitpid(-1, NULL, 0);
		return (0);
	}
	if (pid == 0)
	{
		while (args[++i])
		{
			if (strcmp(args[i], "env") == 0)
				my_env(args);
			if (strcmp(args[i], "echo") == 0 || strcmp(args[i], "env") == 0)
				exit(0);
		}
		my_exec(str, mypath, environ, args);
		exit(0);
	}
	return (-1);
}

int	check_strcmp(char *str, char **mypath)
{
	int		i;
	char	**cmd;

	i = -1;
	cmd = ft_split(str, ' ');
	if (getenv("PATH") == NULL)
		while (mypath[++i])
			mypath[i] = NULL;
	if (strncmp(cmd[0], "pwd", 3) == 0)
		return(my_pwd(cmd));
	else if (strcmp(cmd[0], "cd") == 0)
		return (my_cd(str));
	else if (strcmp(cmd[0], "echo") == 0)
		return (my_echo(cmd));
	else if (strcmp(cmd[0], "export") == 0)
		return (my_exp(str));
	else if (strcmp(cmd[0], "unset") == 0)
		return (my_unset(cmd[1]));
	else if (check_command(str, mypath, cmd) == 0)
		return (0);
	return (-1);
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
			buff = rem_char(buff, 92);
        	if (check_quotes(buff, 0) > 0)
				buff = quotes_resolve(buff, check_quotes(buff, 0));
        	else if (strncmp(buff, "exit", 4) == 0 && (buff[4] == ' ' || buff[4] == '\0'))
        	    break ;
        	else if (check_semicolon(buff, mypath) == -1)
        	        if (check_strcmp(buff, mypath) == -1)
        	            printf("zsh: command not found: %s\n", buff);
        	free(buff);
		}
    }
    return (0);
}
