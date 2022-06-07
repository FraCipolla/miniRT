/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:28:12 by mcipolla          #+#    #+#             */
/*   Updated: 2022/06/07 13:39:42 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_env(char *str)
{
	extern char **environ;
	int			i;
	char		*tmp;	

	i = 4;
	tmp = NULL;
	while (str[i])
	{
		if (str[i] != ' ')
		{
			tmp = ret_word(str + i);
			return(printf("env: %s: No such file or directory\n", tmp));
		}
		i++;
	}
	i = -1;
	while (environ[++i])
		printf("%s\n", environ[i]);
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

char	**cpy_matrix(char **matrix)
{
	int		i;
	char	**ret;

	i = 0;
	ret = malloc(sizeof(char *) * strlen(*matrix) + 1);
	while (matrix[i])
	{
		ret[i] = ft_strjoin(ret[i], matrix[i]);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

int	my_exp(char *str)
{
	extern char **environ;
	int			i;
	char		*tmp;
	static char	**export;

	i = 6;
	export = cpy_matrix(environ);
	export = sort_env(export);
	while (str[i])
	{
		if (str[i] != ' ')
		{
			tmp = ret_word(str + i);
			environ = add_env(environ, tmp);
			return (0);
		}
		i++;
	}
	i = -1;
	while (export[++i])
		printf("%s\n", export[i]);
	return (0);
}

char	**remove_env(char **env, char *search)
{
	int		i;
	int		c;
	char	**ret;

	i = 0;
	c = 0;
	ret = malloc(sizeof(char *) * strlen(*env));
	while (env[i])
	{
		if (strncmp(search, env[i], strlen(search)) != 0)
		{
			ret[c] = ft_strjoin(ret[c], env[i]);
			c++;
		}
		i++;
	}
	ret[c] = NULL;
	return (ret);
}

int	my_unset(char *str)
{
	extern char **environ;
	char		*tmp;
	int			i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	tmp = ret_word(str + i);
	if (str[0] == '\0')
		printf("unset: not enought arguments");
	else if (str[0] != ' ')
		printf("zsh: command not found: unset%s\n", tmp);
	i = 0;
	while (environ[i])
	{
		if (strncmp(environ[i], tmp, strlen(tmp)) == 0)
			environ = remove_env(environ, tmp);
		i++;
	}
	return (0);
}