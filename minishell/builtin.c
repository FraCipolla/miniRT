/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:28:12 by mcipolla          #+#    #+#             */
/*   Updated: 2022/07/17 18:22:49 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_exp(char **tmp)
{
	extern char	**environ;
	int			i;
	char		**export;

	i = 0;
	export = cpy_matrix(environ, 0);
	export = sort_env(export);
	if (tmp[++i] != NULL)
	{
		environ = add_env(environ, tmp[i]);
		return (0);
	}
	i = -1;
	while (export[++i])
	{
		if (check_empty_env(export[i]) == -2)
			export[i] = ft_strjoin(export[i], "''");
		else if (check_empty_env(export[i]) == 0)
			export[i] = ft_strjoin(export[i], "=''");
		printf("%s\n", export[i]);
	}
	return (0);
}

void	my_env( char **tmp)
{
	extern char	**environ;
	int			i;
	int			s;

	if (tmp[1] != NULL)
	{
		if (check_env_path(tmp[1], environ) == -1)
		{
			printf("env: %s: No such file or directory\n", tmp[1]);
			exit (0);
		}
	}
	i = -1;
	while (environ[++i])
	{
		s = check_empty_env(environ[i]);
		if (s == -1 || s == -2)
		{
			if (s == -2)
				printf("%s''\n", environ[i]);
			else
				printf("%s\n", environ[i]);
		}
	}
	exit (0);
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

char	*until_ugual(char *str)
{
	int		i;
	char	*ret;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '\0')
		return (NULL);
	ret = malloc(sizeof(char) * i);
	ret[i] = '\0';
	i = 0;
	while (str[i] != '=')
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = str[i];
	return (ret);
}

char	**add_env(char **env, char *str)
{
	int		i;
	char	**tmp;

	i = -1;
	while (env[++i])
	{
		if (until_ugual(str) != NULL && until_ugual(env[i]) != NULL)
		{
			if (strcmp(until_ugual(str), until_ugual(env[i])) == 0)
			{
				env[i] = ft_strdup(str);
				return (env);
			}
		}
		if (strncmp(str, env[i], ft_strlen(str)) == 0)
			if (env[i][ft_strlen(str)] == '=')
				return (env);
	}
	tmp = cpy_matrix(env, -1);
	i = -1;
	while (env[++i])
		tmp[i] = env[i];
	tmp[i] = str;
	tmp[i + 1] = NULL;
	return (tmp);
}
