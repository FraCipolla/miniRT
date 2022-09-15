/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 10:28:05 by mcipolla          #+#    #+#             */
/*   Updated: 2022/09/07 12:17:00 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	action(int sig)
{
	write(0, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	signal(sig, action);
}

void	clt_echo(char *str)
{
	char		**stty;
	extern char	**environ;
	int			pid;

	pid = fork();
	if (pid == 0)
	{
		stty = malloc(sizeof(char *) * 3);
		stty[0] = ft_strdup("stty");
		stty[1] = ft_strdup(str);
		stty[2] = NULL;
		execve("/bin/stty", stty, environ);
	}
	if (pid > 0)
		waitpid(-1, NULL, 0);
}

char	*get_env(char *str)
{
	int		i;
	char	*ret;

	i = 0;
	while (str[i] != '\0' && str[i] != ' '
		&& str[i] != '"' && str[i] != '$' && str[i] != '\'')
		i++;
	ret = malloc(sizeof(char) * i + 1);
	i = 0;
	while (str[i] != ' ' && str[i] != '\0'
		&& str[i] != '"' && str[i] != '$' && str[i] != '\'')
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

char	*resolve_env(char *str, int j)
{
	int		i;
	int		c;
	char	ret[1024];
	char	*env;

	i = j;
	c = 0;
	while (str[i] && str[i] != '"')
	{
		if (str[i] == '$')
		{
			env = getenv(get_env(str + (++i)));
			while (str[i] && str[i] != ' ' && str[i]
				!= '"' && str[i] != '$' && str[i] != '\'')
					i++;
			while (env && *env)
					ret[c++] = *env++;
		}
		else
			ret[c++] = str[i++];
	}
	ret[c] = '\0';
	env = ft_strdup(ret);
	return (env);
}

char	**remove_quotes(char **args)
{
	int		i;
	char	**ret;

	i = 0;
	while (args[i])
		i++;
	ret = (char **)malloc(sizeof(char *) * i + 1);
	i = -1;
	while (args[++i])
	{
		if (args[i][0] == 34 || args[i][0] == 39)
		{
			if (args[i][0] == 34)
				ret[i] = ft_strdup(resolve_env(args[i], 1));
			else
			{
				ret[i] = ft_strdup(args[i] + 1);
				ret[i][ft_strlen(args[i]) - 2] = '\0';
			}
		}
		else
			ret[i] = resolve_env(args[i], 0);
	}
	ret[i] = NULL;
	return (ret);
}
