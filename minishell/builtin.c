/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:28:12 by mcipolla          #+#    #+#             */
/*   Updated: 2022/06/11 21:02:14 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	my_env( char **tmp)
{
	extern char **environ;
	int			i;

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
		if (check_empty_env(environ[i]) == -1)
			printf("%s\n", environ[i]);
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

/* CONTROLLARE QUESTA FUNZIONE*/

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
	while (ret[i])
	{
		ret[i] = str[i];
		i++;
	}
	return (ret);
}

char	**add_env(char **env, char *str)
{
	int		i;
	char	**tmp;

	i = -1;
	while (env[++i])
	{
		if (strcmp(until_ugual(str), until_ugual(env[i])) == 0)
		{
			env[i] = ft_strdup(str);
			return (env);
		}
	}
	i = 0;
	tmp = cpy_matrix(env, -1);
	while (env[i])
	{
		tmp[i] = env[i];
		i++;
	}
	tmp[i] = str;
	tmp[i + 1] = NULL;
	return (tmp);
}

char	**cpy_matrix(char **matrix, int	offset)
{
	int		i;
	char	**ret;

	i = 0;
	while (matrix[i])
		i++;
	ret = malloc(sizeof(char *) * (i + 1 - offset));
	i = 0;
	while (matrix[i + offset])
	{
		ret[i] = ft_strdup(matrix[i]);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

int	my_exp(char *str)
{
	extern char **environ;
	int			i;
	char		**tmp;
	char		**export;

	i = 0;
	tmp = ft_split(str, ' ');
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
		if (check_empty_env(export[i]) == 0)
			export[i] = ft_strjoin(export[i], "=''");
		printf("%s\n", export[i]);
		// free(export[i]);
	}
	// free(export);
	return (0);
}

char	**remove_env(char **env, char *search)
{
	int		i;
	int		c;
	char	**ret;

	i = 0;
	c = 0;
	ret = malloc(sizeof(char *) * ft_strlen(*env));
	while (env[i])
	{
		if (strncmp(search, env[i], ft_strlen(search)) != 0)
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
		if (strncmp(environ[i], tmp, ft_strlen(tmp)) == 0)
			environ = remove_env(environ, tmp);
		i++;
	}
	return (0);
}