/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 20:07:25 by mcipolla          #+#    #+#             */
/*   Updated: 2022/06/20 17:04:41 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redir(char **args)
{
	int		fd;
	int		i;

	i = -1;
	while (args[++i])
	{
		if (strcmp(args[i] , ">") == 0)
		{
			fd = open(args[i + 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
			dup2(fd, 1);
		}
		// else if (strcmp(args[i] , ">>") == 0)
		// {
		// 	fd = open(args[i + 1], O_CREAT | O_RDWR | O_APPEND, 0644);
		// 	dup2(fd, 1);
		// }
		// else if (strcmp(args[i] , "<") == 0)
		// {
		// 	fd = open(args[i + 1], O_RDONLY, 0644);
		// 	dup2(fd, 0);
		// }
	}
	return (-1);
}

int	check_semicolon(char *str, char **mypath)
{
	int		i;
	char	**cmds;

	cmds = ft_split(str, ';');
	if (cmds[0] == NULL)
		return (-1);
	else
	{
		i = 0;
		while (cmds[i])
		{
			if (check_strcmp(cmds[i], mypath) == -1)
				printf("zsh: command not found: %s\n", cmds[i]);
			i++;
		}
	}
	return (0);
}

int	check_quotes(char *str, int flag)
{
	int	i;
	int	count;
	int	count2;

	i = 0;
	count = 0;
	count2 = 0;
	while (str[i])
	{
		if (str[i] == 39)
			count++;
		if (str[i] == 34)
			count2++;
		i++;
	}
	if (count % 2 != 0 && flag != 34)
		return (39);
	else if (count2 % 2 != 0 && flag != 39)
		return (34);
	else
		return (0);
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
