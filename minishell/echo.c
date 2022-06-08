/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 13:24:40 by mcipolla          #+#    #+#             */
/*   Updated: 2022/06/08 20:25:07 by mcipolla         ###   ########.fr       */
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

void	my_echo(char *str, char **str2)
{
	int		fd;
	char	*cmd;
	int		i;

	if (strncmp(str, "-n", 2) == 0)
		i = 2;
	else
		i = -1;
	if (check_redir(str2) == -1)
	{
		while (str[++i])
			if (check_char(str + i) == 0)
				write(1, &str[i], 1);
		if (strncmp(str, "-n", 2) != 0)
			printf("\n");
		else
			printf("%%\n");
	}
	else
	{
		cmd = NULL;
		str2++;
		if (strcmp(*str2, "-n") == 0)
			str2++;
		while (strncmp(*str2, ">", 1) != 0 && *str2 != NULL)
		{
			cmd = ft_strjoin(cmd, *str2);
			cmd = ft_strjoin(cmd, " ");
			str2++;
		}
		str2++;
		fd = open(*str2, O_CREAT | O_RDWR | O_TRUNC, 0644);
		write(fd, cmd, strlen(cmd));
	}
	exit(0);
}