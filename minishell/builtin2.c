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

int	my_unset(char *str)
{
	extern char	**environ;
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

char	**cpy_matrix(char **matrix, int offset)
{
	int		i;
	char	**ret;

	i = 0;
	while (matrix[i])
		i++;
	ret = (char **)malloc(sizeof(char *) * (i + 1 - offset));
	i = 0;
	while (matrix[i])
	{
		ret[i] = matrix[i];
		i++;
	}
	ret[i + 1] = NULL;
	return (ret);
}

void	here_doc(char *limiter, int *end)
{
	char	*buff;
	char	*ret;

	ret = NULL;
	while (1)
	{
		buff = readline("heredoc> ");
		if (strcmp(buff, limiter) == 0)
			break ;
		ret = ft_strjoin(ret, buff);
		ret = ft_strjoin(ret, "\n");
	}
	write(end[1], ret, ft_strlen(ret));
	close(end[1]);
	dup2(end[0], 0);
	free(buff);
}
