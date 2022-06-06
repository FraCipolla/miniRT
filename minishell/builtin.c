/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:28:12 by mcipolla          #+#    #+#             */
/*   Updated: 2022/06/06 22:15:24 by mcipolla         ###   ########.fr       */
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
	i = 4;
	tmp = NULL;
	while (str[i])
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
		i++;
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
	i = 0;
	while (env[i + 1])
	{
		if (strcmp(env[i], env[i + 1]) > 0 && env[i])
		{
			tmp = env[i];
			env[i] = env[i + 1];
			env[i + 1] = tmp;
			i = 0;
		}
		i++;
	}
	return (env);
}

char	**add_env(char **env, char *str)
{
	int		i;
	char	**tmp;

	tmp = malloc(sizeof(char *) * strlen(*env) + 2);
	i = 0;
	while (env[i])
	{
		tmp[i] = env[i];
		i++;
	}
	tmp[i] = str;
	tmp[i + 1] = NULL;
	return (tmp);
}

char	**my_exp(char *str)
{
	extern char **environ;
	int			i;
	int			c;
	char		*tmp;	

	c = 0;
	i = 6;
	tmp = NULL;
	environ = sort_env(environ);
	while (str[i])
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
			environ = add_env(environ, tmp);
			return (environ);
		}
		i++;
	}
	while (*environ)
	{
		printf("%s\n", *environ);
		environ++;
	}
	return (environ);
}
