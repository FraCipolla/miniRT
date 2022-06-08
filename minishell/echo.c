/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 13:24:40 by mcipolla          #+#    #+#             */
/*   Updated: 2022/06/08 15:33:55 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redir(char **str)
{
	while (*str)
	{
		if (strcmp(*str, ">") == 0)
			return (0);
		str++;
	}
	return (-1);
}

void	my_echo(char **str)
{
	int		fd;
	char	*cmd;
	int		i;

	i = 0;
	cmd = NULL;
	if (check_redir(str) == -1)
	{
		while (str[++i])
			printf("%s ", str[i]);
		printf("\n");
	}
	else
	{
		i++;
		while (strncmp(str[i], ">", 1) != 0 && str[i] != '\0')
		{
			cmd = ft_strjoin(cmd, str[i]);
			cmd = ft_strjoin(cmd, " ");
			i++;
		}
		i++;
		fd = open(str[i], O_CREAT | O_RDWR | O_TRUNC, 0644);
		write(fd, cmd, strlen(cmd));
	}
	exit(0);
}