/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:28:12 by mcipolla          #+#    #+#             */
/*   Updated: 2022/10/08 16:45:07 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_unset(char **str, char **envp)
{
	int			i;
	int			c;
	char		*swap;

	c = 0;
	while (str[++c])
	{
		i = -1;
		while (envp[++i])
		{
			if (strncmp(str[c], envp[i], ft_strlen(str[c])) == 0
				&& envp[i][ft_strlen(str[c])] == '=')
			{
				swap = envp[i];
				while (envp[i + 1] != NULL)
				{
					envp[i] = envp[i + 1];
					i++;
				}
				envp[i] = swap;
				envp[i][0] = '\0';
			}
		}
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
