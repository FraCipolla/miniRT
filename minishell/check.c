/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 20:07:25 by mcipolla          #+#    #+#             */
/*   Updated: 2022/07/07 14:44:36 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc(char *limiter, int *end)
{
	char	*buff;
	char	*ret;
	
	ret = NULL;
	while(1)
	{
		buff = readline("heredoc> ");
		if (strcmp(buff, limiter) == 0)
			break ;
		ret = ft_strjoin(ret, buff);
		ret = ft_strjoin(ret, "\n");
	}
	write (end[1], ret, ft_strlen(ret));
	close(end[1]);
	dup2(end[0], 0);
	free(buff);
}

int	check_redir(char **args)
{
	int		fd;
	int		i;
	int		end[2];

	i = -1;
	pipe(end);
	while (args[++i])
	{
		if (i != -1 && (strcmp(args[i], ">") == 0 || strcmp(args[i], ">>") == 0))
		{
			if (strcmp(args[i], ">") == 0)
				fd = open(args[i + 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
			else
				fd = open(args[i + 1], O_CREAT | O_RDWR | O_APPEND, 0644);
			dup2(fd, 1);
		}
		if (strcmp(args[i] , "<") == 0)
		{
			fd = open(args[i + 1], O_RDONLY, 0644);
			dup2(fd, 0);
		}
		if (strcmp(args[i] , "<<") == 0)
			here_doc(args[i + 1], end);
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
