/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 17:25:45 by mcipolla          #+#    #+#             */
/*   Updated: 2022/10/03 15:32:26 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_wild(char *wild_str, char *str)
{
	char	**splitted;
	int		i;
	int		size;

	i = 0;
	splitted = ft_split(wild_str, '*');
	size = strlen(wild_str);
	if (wild_str[0] != '*' && str[0] != wild_str[0])
		return (0);
	if (wild_str[size] != '*' && str[strlen(str)] != wild_str[size])
		return (0);
	while (*str && splitted[i])
	{
		if (*str == splitted[i][0] && strstr(str, splitted[i]) == str)
			i++;
		str++;
	}
	if (!splitted[i])
	{
		my_free(splitted);
		return (1);
	}
	my_free(splitted);
	return (0);
}

char	*parse_files(char *wild)
{
	DIR				*d;
	struct dirent	*dir;
	char			*ret;

	ret = NULL;
	d = opendir(".");
	if (d)
	{
		dir = readdir(d);
		while (dir != NULL)
		{
			if (parse_wild(wild, dir->d_name) == 1)
			{
				ret = ft_strjoin(ret, dir->d_name);
				ret = ft_strjoin(ret, " ");
			}
			dir = readdir(d);
		}
	}
	closedir(d);
	return (ret);
}

char	**check_wild(char **args)
{
	int		i;
	char	**ret;
	char	*tmp;
	char	*aux;

	i = -1;
	tmp = NULL;
	while (args[++i])
	{
		if (strchr(args[i], '*') != NULL)
		{
			aux = parse_files(args[i]);
			tmp = ft_strjoin(tmp, aux);
			free(aux);
		}
		else
			tmp = ft_strjoin(tmp, args[i]);
		tmp = ft_strjoin(tmp, " ");
	}
	ret = ft_split(tmp, ' ');
	free(tmp);
	my_free(args);
	return (ret);
}
