/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 13:24:40 by mcipolla          #+#    #+#             */
/*   Updated: 2022/06/10 12:41:59 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redir(char **str)
{
	while (*str)
	{
		if (strcmp(*str , ">") == 0)
			return (0);
		str++;
	}
	return (-1);
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

void	my_echo(char **str2)
{
	int		fd;
	char	*cmd;
	int		i;

	i = -1;
	cmd = str_to_print(str2);
	if (check_redir(str2) == -1)
	{
		while (str2[++i])
			if (strcmp(str2[i], "-n") == 0)
				cmd[ft_strlen(cmd) - 1] = '%';
		printf("%s\n", cmd);
	}
	else
	{
		while (strncmp(*str2, ">", 1) != 0 && *str2 != NULL)
			str2++;
		cmd[ft_strlen(cmd)] = '\n';
		cmd = ft_strjoin(cmd, "\0");
		str2++;
		fd = open(*str2, O_CREAT | O_RDWR | O_TRUNC, 0644);
		write(fd, cmd, strlen(cmd));
	}
	exit(0);
}