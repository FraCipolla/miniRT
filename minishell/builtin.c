/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:28:12 by mcipolla          #+#    #+#             */
/*   Updated: 2022/06/06 20:03:17 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_env(char *str)
{
	extern char **environ;
	int			i;
	int			c;
	char		*tmp;	

	c = 0;
	i = 3;
	tmp = NULL;
	while (str[++i])
	{
		if (str[i] != ' ')
		{
			while (str[i] != ' ' && str[i])
			{
				c++;
				i++;
			}
			tmp = malloc(sizeof(char) * c + 1);
			tmp[c] = '\0';
			i -= c;
			c = 0;
			while (str[i] != ' ' && str[i])
			{
				tmp[c] = str[i];
				c++;
				i++;
			}
			return(printf("env: %s: No such file or directory\n", tmp));
		}
	}
	while (*environ)
	{
		printf("%s\n", *environ);
		environ++;
	}
	return (0);
}

char	**sort_env(char **env)
{
	char	*tmp;
	int		i;

	tmp = NULL;
	i = -1;
	while(env[++i])
	{
		i = -1;
		while (env[++i])
		{
			if (strcmp(env[i], env[i + 1]) > 0)
			{
				tmp = env[i];
				env[i] = env[1 + 1];
				env[i + 1] = tmp;
				break ;
			}
		}
	}
	return (env);
}

int	my_exp(char *str)
{
	extern char **environ;
	int			i;
	int			c;
	char		*tmp;	

	c = 0;
	i = 6;
	tmp = NULL;
	while (str[++i])
	{
		if (str[i] != ' ')
		{
			while (str[i] != ' ' && str[i])
			{
				c++;
				i++;
			}
			tmp = malloc(sizeof(char) * c + 1);
			tmp[c] = '\0';
			i -= c;
			c = 0;
			while (str[i] != ' ' && str[i])
			{
				tmp[c] = str[i];
				c++;
				i++;
			}
			return(printf("env: %s: No such file or directory\n", tmp));
		}
	}
	environ = sort_env(environ);
	while (*environ)
	{
		printf("%s\n", *environ);
		environ++;
	}
	return (0);
}
