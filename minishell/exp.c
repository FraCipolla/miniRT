/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:28:12 by mcipolla          #+#    #+#             */
/*   Updated: 2022/09/30 18:35:48 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_exp(char **tmp)
{
	extern char	**environ;
	int			i;
	char		**export;
	char		*aux;

	i = 0;
	while (tmp[++i] != NULL)
		environ = add_env(environ, tmp[i]);
	if (tmp[1] != NULL)
		return (0);
	i = -1;
	export = cpy_matrix(environ, 0);
	export = sort_env(export);
	while (export[++i])
	{
		if (check_empty_env(export[i]) == -2)
			aux = ft_strjoin(export[i], "''");
		else if (check_empty_env(export[i]) == 0)
			aux = ft_strjoin(export[i], "=''");
		else
			aux = ft_strdup(export[i]);
		printf("%s\n", aux);
		free(aux);
	}
	my_free(export);
	return (0);
}

int	my_env( char **tmp)
{
	extern char	**environ;
	int			i;
	int			s;

	if (tmp[1] != NULL)
	{
		if (check_env_path(tmp[1], environ) == -1)
		{
			printf("env: %s: No such file or directory\n", tmp[1]);
			return (1);
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
			i = -1;
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
	char	*tmp;
	char	*tmp2;

	i = -1;
	while (env[++i])
	{
		tmp = until_ugual(str);
		tmp2 = until_ugual(env[i]);
		if (tmp != NULL && tmp2 != NULL)
		{
			if (strcmp(tmp, tmp2) == 0)
			{
				env[i] = str;
				free(tmp);
				free(tmp2);
				return (env);
			}
		}
		if (strncmp(str, env[i], ft_strlen(str)) == 0)
			if (env[i][ft_strlen(str)] == '=')
				return (env);
	}
	env[i] = str;
	env[i + 1] = NULL;
	return (env);
}
