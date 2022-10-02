/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:28:12 by mcipolla          #+#    #+#             */
/*   Updated: 2022/10/02 19:02:04 by mcipolla         ###   ########.fr       */
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
				remove_env(envp, str[c]);
			i++;
		}
	}
	g_exit = 0;
	return (0);
}

void	remove_env(char **env, char *search)
{
	int		i;
	
	i = -1;
	while (env[++i])
	{
		if (strncmp(search, env[i], ft_strlen(search)) == 0)
		{
			env[i] = "";
		}
	}
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
