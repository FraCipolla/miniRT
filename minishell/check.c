/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 20:07:25 by mcipolla          #+#    #+#             */
/*   Updated: 2022/10/03 19:12:44 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redir(char **args)
{
	int		fd;
	int		i;
	int		end[2];

	i = -1;
	fd = 1;
	pipe(end);
	while (args[++i])
	{
		if (strcmp(args[i], ">") == 0)
			fd = open(args[i + 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (strcmp(args[i], ">>") == 0)
			fd = open(args[i + 1], O_CREAT | O_RDWR | O_APPEND, 0644);
		if (strcmp(args[i], ">") == 0 || strcmp(args[i], ">>") == 0)
			dup2(fd, 1);
		if (strcmp(args[i], "<") == 0)
		{
			fd = open(args[i + 1], O_RDONLY, 0644);
			dup2(fd, 0);
		}
		if (strcmp(args[i], "<<") == 0)
			here_doc(args[i + 1], end);
	}
	return (fd);
}

void	check_aux(int i, int c, int *store, char **tmp)
{
	if (tmp[i][c] == store[0] || tmp[i][c] == store[1])
	{
		store[0] = 0;
		store[1] = 0;
	}
	else if (tmp[i][c] == 34)
		store[0] = 34;
	else if (tmp[i][c] == 39)
		store[1] = 39;
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

int	check_dot(char **cmd, char **environ)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = NULL;
	while (cmd[++i])
		tmp = ft_strjoin(tmp, cmd[i]);
	i = 0;
	while (tmp[i])
	{
		if (strncmp(tmp + i, "./", 2) == 0)
		{
			if (access(cmd[0], R_OK) == 0)
			{
				if (strncmp(tmp + i, "./minishell", 11) == 0)
					ft_increase_shlvl();
				execve(cmd[0], cmd, environ);
			}
			g_exit = 127;
			printf("%s: No such file or directory\n", cmd[0]);
			exit (0);
		}
		i++;
	}
	return (-1);
}
