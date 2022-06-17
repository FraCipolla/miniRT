/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 13:24:40 by mcipolla          #+#    #+#             */
/*   Updated: 2022/06/17 17:05:47 by mcipolla         ###   ########.fr       */
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
		if (strcmp(args[i], ">>") == 0 || args[i][0] == '>' || args[i][0] == '<')
			n++;
	}
	ret = malloc(sizeof(char *) * i - (n * 2) + 1);
	i = -1;
	n = 0;
	while (args[++i])
	{
		if (strcmp(args[i], ">>") == 0 || args[i][0] == '>' || args[i][0] == '<')
			i += 2;
		if (args[i] == NULL)
			break ;
		ret[n] = ft_strdup(args[i]);
		n++;
	}
	ret[n] = NULL;
	return (ret);
}

char	**check_redir(char **args)
{
	int		i;
	int		fd;

	i = 0;
	while (args[i])
	{
		if (strcmp(args[i] , ">") == 0)
		{
			fd = open(args[i + 1], O_CREAT | O_RDWR, 0644);
			dup2(fd, 1);
		}
		else if (strcmp(args[i] , ">>") == 0)
		{
			fd = open(args[i + 1], O_CREAT | O_RDWR | O_APPEND, 0644);
			dup2(fd, 1);
		}
		else if (strcmp(args[i] , "<") == 0)
		{
			fd = open(args[i + 1], O_RDONLY, 0644);
			dup2(fd, 0);
		}
		i++;
	}
	return (cut_red(args));
}

int	check_char(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 33 && str[i] <= 126)
			return (0);
		i++;
	}
	return (-1);
}

char	*str_to_print(char **str2)
{
	char	*ret;
	int		i;

	i = 0;
	ret = NULL;
	while (strcmp(str2[i], "echo") != 0)
		i++;
	if (strcmp(str2[i + 1], "-n") == 0)
		i++;
	i++;
	while (str2[i] && str2[i][0] != '>')
	{
		ret = ft_strjoin(ret, str2[i]);
		ret = ft_strjoin(ret, " ");
		i++;
	}
	return (ret);
}

void	my_echo(char **args)
{
	char	*cmd;
	int		i;

	i = -1;
	cmd = str_to_print(cut_red(args));
	while (args[++i])
		if (strcmp(args[i], "-n") == 0)
			cmd[ft_strlen(cmd) - 1] = '%';
	printf("%s\n", cmd);
	exit(0);
}