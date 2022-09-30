/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:28:12 by mcipolla          #+#    #+#             */
/*   Updated: 2022/09/30 18:05:59 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_unset(char **str)
{
	extern char	**environ;
	int			i;
	int			c;

	c = 0;
	while (str[++c])
	{
		i = 0;
		while (environ[i])
		{
			if (strncmp(str[c], environ[i], ft_strlen(str[c])) == 0
				&& environ[i][ft_strlen(str[c])] == '=')
				environ = remove_env(environ, str[c]);
			i++;
		}
	}
	g_exit = 0;
	return (0);
}

char	**remove_env(char **env, char *search)
{
	int		i;
	int		c;
	char	**ret;

	i = 0;
	c = 0;
	while (env[i])
		i++;
	ret = malloc(sizeof(char *) * i + 1);
	i = -1;
	while (env[++i])
	{
		if (strncmp(search, env[i], ft_strlen(search)) != 0)
		{
			ret[c] = ft_strjoin(ret[c], env[i]);
			c++;
		}
	}
	ret[c] = NULL;
	return (ret);
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
