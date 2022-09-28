/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 10:28:05 by mcipolla          #+#    #+#             */
/*   Updated: 2022/09/28 19:47:04 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(char *str)
{
	int		i;
	char	*ret;

	i = 0;
	while (str[i] != '\0' && str[i] != ' ' && str[i] != '\n'
		&& str[i] != '"' && str[i] != '$' && str[i] != '\'')
		i++;
	ret = malloc(sizeof(char) * i + 1);
	i = 0;
	while (str[i] != ' ' && str[i] != '\0' && str[i] != '\n'
		&& str[i] != '"' && str[i] != '$' && str[i] != '\'')
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

int	check_dollar(char *str, char **ret, int i)
{
	int		c;
	char	tmp[1024];
	char	*env;

	c = 0;
	while (str[i] != '"')
	{
		if (str[i] == '$')
		{
			if (str[++i] == '?')
				env = ft_itoa(g_exit);
			else
				env = getenv(get_env(str + i));
			while (env && *env)
				tmp[c++] = *env++;
			while (str[i] && str[i] != ' ' && str[i] != '"'
				&& str[i] != '$' && str[i] != '\'' && str[i] != '\n')
				i++;
		}
		else if (str[i])
			tmp[c++] = str[i++];
	}
	tmp[c] = '\0';
	*ret = ft_strjoin(*ret, tmp);
	return (i + 1);
}

// int	between_quotes(char *str, char **ret)
// {
// 	int		i;
// 	int		c;
// 	char	*tmp;

// 	i = 1;
// 	while (str[i] != '\'')
// 		i++;
// 	tmp = malloc(sizeof(char) * i - 1);
// 	tmp[i - 1] = '\0';
// 	i = 1;
// 	c = 0;
// 	while (str[i] != '\'')
// 	{
// 		tmp[c] = str[i];
// 		i++;
// 		c++;
// 	}
// 	*ret = ft_strjoin(*ret, tmp);
// 	return (i + 1);
// }

int manage_sq(char *first, char **toret)
{
	char *next;
	char *aux;

	next = strstr(first, "'");
	if((next - first) == 1)
		return (1);
	aux = ft_malloc_strcpy(first, next - first);
	*toret = ft_strjoin(*toret,aux);
	free(aux);
	return(next - first + 2);
}

char	*resolve_env(char *str)
{
	int		i;
	char	*ret;

	i = 0;
	ret = NULL;
	while (*str && str)
	{
		if (*str == '\'')
			str += manage_sq(str + 1, &ret);
		else if (*str == '"')
			str += check_dollar(str, &ret, 1);
		else if (*str == '$')
		{
			ret = ft_strjoin(ret, getenv(get_env(++(str))));
			while (*str && *str != ' ' && *str != '"'
				&& *str != '$' && *str != '\'' && *str != '\n')
				str++;
		}
		else
		{
			add_char(&ret, *str);
			str++;
		}
	}
	return (ret);
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
		if (strchr(args[i], 34) != NULL || strchr(args[i], 39) != NULL)
			ret[i] = resolve_env(args[i]);
		else
			ret[i] = resolve_env(args[i]);
	}
	ret[i] = NULL;
	return (ret);
}
