/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirUtils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:28:12 by mcipolla          #+#    #+#             */
/*   Updated: 2022/07/17 18:22:49 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**cut_red(char **args)
{
	int		i;
	int		n;
	char	**ret;

	i = -1;
	n = 0;
	while (args[++i])
	{
		if (strcmp(args[i], ">>") == 0 || args[i][0] == '>' || args[i][0] == '<' || strcmp(args[i], "<<") == 0)
			n++;
	}
	ret = malloc(sizeof(char *) * i - (n * 2) + 1);
	i = -1;
	n = 0;
	while (args[++i])
	{
		if (strcmp(args[i], ">>") == 0 || args[i][0] == '>' || args[i][0] == '<' || strcmp(args[i], "<<") == 0)
			i++;
		else
		{
			ret[n] = ft_strdup(args[i]);
			n++;
		}
	}
	ret[n] = NULL;
	return (ret);
}

int	memcmp_aux(int i, char **args)
{
	if (!memcmp(args[i], ">\0", 2) || !memcmp(args[i], ">>\0", 3)
		|| !memcmp(args[i], "<\0", 2) || !memcmp(args[i], "<<\0", 3))
		return (1);
	return (0);
}

int	cut_red_aux(char **args)
{
	int	i;
	int	n;

	i = -1;
	n = 0;
	while (args[++i])
	{
		if (memcmp_aux(i, args))
			n += 2;
		else if (args[i][0] == '>' || args[i][0] == '<')
			n++;
	}
	return (n);
}

int	check_redir_aux1(char **args, int i)
{
	int	fd;

	fd = 1;
	if (memcmp(args[i], ">\0", 2) == 0 || memcmp(args[i], ">>\0", 3) == 0)
	{
		if (memcmp(args[i], ">\0", 2) == 0)
			fd = open(args[i + 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
		else
			fd = open(args[i + 1], O_CREAT | O_RDWR | O_APPEND, 0644);
		dup2(fd, 1);
	}
	else if (args[i][0] == '>')
	{
		if (!strncmp(args[i], ">>", 2))
			fd = open(args[i] + 2, O_CREAT | O_RDWR | O_APPEND, 0644);
		else
			fd = open(args[i] + 1, O_CREAT | O_RDWR | O_TRUNC, 0644);
		dup2(fd, 1);
	}
	return (fd);
}

int	check_redir_aux2(char **args, int i, int *end)
{
	int	fd;

	fd = 1;
	if (memcmp(args[i], "<\0", 2) == 0 || memcmp(args[i], "<<\0", 3) == 0)
	{
		if (memcmp(args[i], "<\0", 2) == 0)
			fd = open(args[i + 1], O_RDONLY, 0644);
		else
			here_doc(args[i + 1], end);
		dup2(fd, 0);
	}
	else if (args[i][0] == '<')
	{
		if (!strncmp(args[i], "<<", 2))
			here_doc(args[i] + 2, end);
		else
			fd = open(args[i] + 1, O_RDONLY, 0644);
		dup2(fd, 1);
	}
	return (fd);
}
