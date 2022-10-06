/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:28:12 by mcipolla          #+#    #+#             */
/*   Updated: 2022/10/06 18:38:36 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_unset(char **str, char **envp)
{
	int			i;
	int			c;

	c = 0;
	while (str[++c])
	{
		i = 0;
		while (envp[i])
		{
			if (strncmp(str[c], envp[i], ft_strlen(str[c])) == 0
				&& envp[i][ft_strlen(str[c])] == '=')
			{
				while (envp[i + 1] != NULL)
				{
					envp[i] = envp[i + 1];
					i++;
				}
			}
			i++;
		}
		envp[i - 1][0] = '\0';
	}
	g_exit = 0;
	return (g_exit);
}

int	check_env_path(char *str, char **environ)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			while (*environ)
			{
				if (strncmp(*environ, str, i) == 0)
					return (0);
				environ++;
			}
			break ;
		}
		i++;
	}
	return (-1);
}
