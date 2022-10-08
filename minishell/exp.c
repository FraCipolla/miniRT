/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:28:12 by mcipolla          #+#    #+#             */
/*   Updated: 2022/10/08 16:56:59 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_exp(char **tmp, char **envp)
{
	int			i;
	char		**export;
	char		*aux;

	i = 0;
	if (tmp[1] != NULL)
		while (tmp[++i] != NULL)
			add_env(tmp[i], &envp[0]);
	if (tmp[1] != NULL)
		return (0);
	export = cpy_matrix(envp, -1);
	export = sort_env(export);
	i = -1;
	while (export[++i])
	{
		if (check_empty_env(export[i]) == -2)
			aux = ft_strjoin(export[i], "''");
		else if (check_empty_env(export[i]) == 0)
			aux = ft_strjoin(export[i], "=''");
		else
			aux = ft_strdup(export[i]);
		printf("declare -x %s\n", aux);
		free(aux);
	}
	my_free(export);
	return (0);
}

int	my_env( char **tmp, char **envp)
{
	int			i;
	int			s;

	if (tmp[1] != NULL)
	{
		if (check_env_path(tmp[1], envp) == -1)
		{
			printf("env: %s: No such file or directory\n", tmp[1]);
			return (1);
		}
	}
	i = -1;
	while (envp[++i])
	{
		s = check_empty_env(envp[i]);
		if (s == -1 || s == -2)
		{
			if (s == -2)
				printf("%s''\n", envp[i]);
			else
				printf("%s\n", envp[i]);
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
		if (env[i] && strcmp(env[i], env[i + 1]) > 0)
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

int	until_ugual(char *s1, char *s2)
{
	int	i;
	int	c;

	i = 0;
	while (s1[i] && s1[i] != '=')
		i++;
	if (s1[i] == '\0')
		return (1);
	c = 0;
	while (s2[c] && s2[c] != '=')
		c++;
	if (s2[i] == '\0')
		return (1);
	if (i == c && strncmp(s1, s2, i) == 0)
		return (0);
	return (1);
}

void	add_env(char *str, char **envp)
{
	int			i;
	int			c;
	
	i = -1;
	while (envp[++i])
	{
		if (until_ugual(str, envp[i]) == 0)
		{
			c = 0;
			while (envp[i][c] != '=')
				c++;
			while (str[++c])
				envp[i][c] = str[c];
			return ;
		}
		if (strncmp(str, envp[i], ft_strlen(str)) == 0)
			if (envp[i][ft_strlen(str)] == '=')
				return ;
	}
	envp[i] = ft_strdup(str);
	envp[i + 1] = NULL;
}
