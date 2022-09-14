/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 20:07:25 by mcipolla          #+#    #+#             */
/*   Updated: 2022/09/07 14:47:33 by mcipolla         ###   ########.fr       */
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
		if (args[i][0] == '<')
			fd = check_redir_aux2(args, i, end);
		else
			fd = check_redir_aux1(args, i);
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

int	check_quotes(char **tmp, int flag)
{
	int		i;
	int		c;
	int		store[2];

	i = -1;
	store[0] = 0;
	store[1] = 0;
	while (tmp[++i])
	{
		c = -1;
		while (tmp[i][++c])
		{
			if (tmp[i][c] == flag)
				return (flag);
			else
				check_aux(i, c, store, tmp);
		}
	}
	if (store[0] > store[1])
		return (store[0]);
	return (store[1]);
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

	i = 0;
	while (cmd[i])
	{
		if (strncmp(cmd[i], "./", 2) == 0)
		{
			if (access(cmd[0], R_OK) == 0)
			{
				if (strncmp(cmd[i], "./minishell", 11) == 0)
					ft_increase_shlvl();
				execve(cmd[0], cmd, environ);
			}
			printf("zsh: no such file or directory: %s\n", cmd[0]);
			exit (0);
		}
		i++;
	}
	return (-1);
}
