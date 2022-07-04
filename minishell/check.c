/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 20:07:25 by mcipolla          #+#    #+#             */
/*   Updated: 2022/07/04 19:53:55 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redir(char **args)
{
	int		fd;
	int		i;
	char	*buff;
	int		end[2];

	pipe(end);
	i = -1;
	while (args[++i])
	{
		if (strcmp(args[i] , "<") == 0)
		{
			fd = open(args[i + 1], O_RDONLY, 0644);
			buff = get_next_line(fd);
			write(end[1], buff, ft_strlen(buff));
			free(buff);
		}
	}
	i = -1;
	while (args[++i])
	{
		if (strcmp(args[i], ">") == 0)
			if (fork() > 0)
			{
				fd = open(args[i + 1], O_CREAT | O_RDWR, 0644);
				dup2(fd, 1);
				break;
			}
	}
	// while (args[i])
	// {
	// 	printf("%s\n", args[i + 1]);
	// 	if (strcmp(args[i] , ">") == 0)
	// 	{
	// 		fd = open(args[i + 1], O_CREAT | O_RDWR, 0644);
	// 		dup2(fd, 1);
	// 		break;
	// 	}
	// 	i++;
	// 	// else if (strcmp(args[i] , ">>") == 0)
	// 	// {
	// 	// 	fd = open(args[i + 1], O_CREAT | O_RDWR | O_APPEND, 0644);
	// 	// 	dup2(fd, 1);
	// 	// }
	// }
	close(end[1]);
	dup2(end[0], 0);
	return (0);
}

int	check_semicolon(char *str, char **mypath)
{
	int			i;
	char		**cmds;
	extern char	**environ;

	cmds = ft_split(str, ';');
	if (cmds[1] == NULL)
		return (-1);
	else
	{
		i = 0;
		while (cmds[i])
		{
			if (check_strcmp(cmds[i], mypath, environ) == -1)
				printf("zsh: command not found: %s\n", cmds[i]);
			i++;
		}
	}
	return (0);
}

int	check_quotes(char **tmp, int flag)
{
	int		i;
	int		c;
	int		store;
	int		store2;

	i = -1;
	store = 0;
	store2 = 0;
	while (tmp[++i])
	{
		c = -1;
		while (tmp[i][++c])
		{
			if (tmp[i][c] == flag)
				return (flag);
			else if (tmp[i][c] == store || tmp[i][c] == store2)
			{
				store = 0;
				store2 = 0;	
			}
			else if (tmp[i][c] == 34)
				store = 34;
			else if (tmp[i][c] == 39)
				store2 = 39;
		}
	}
	if (store > store2)
		return (store);
	return(store2);
}

int	check_empty_env(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=' && str[i + 1] == '\0')
			return (-2);
		else if (str[i] == '=')
			return (-1);
		i++;
	}
	return (0);
}
