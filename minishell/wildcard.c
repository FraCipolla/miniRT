/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 17:25:45 by mcipolla          #+#    #+#             */
/*   Updated: 2022/09/22 18:04:54 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int parse_wild(char *wild_str, char *str)
{
    char    **splitted;
    int     i;
    int     size;
    i = 0;
    splitted = ft_split(wild_str, '*');
    size = strlen(wild_str);
    if (wild_str[0] != '*' && str[0] != wild_str[0])
        return 0;
    if (wild_str[size] != '*' && str[strlen(str)] != wild_str[size])
        return 0;
    while(*str && splitted[i])
    {
        if(*str == splitted[i][0] && strstr(str, splitted[i]) == str)
            i++;
        str++;
    }
    if (!splitted[i])
        return 1;
    return 0;
}

char	*parse_files(char *wild)
{
	DIR 			*d;
	struct dirent	*dir;
	char			*ret;

	ret = NULL;
	d = opendir(".");
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
		{
			if (parse_wild(wild, dir->d_name) == 1)
			{
				ret = ft_strjoin(ret, dir->d_name);
				ret = ft_strjoin(ret, " ");
			}
		}
	}
	closedir(d);
	return (ret);
}

char	**check_wild(char **args)
{
	int		i;
	int		c;
	char	**ret;
	char	*tmp;

	i = -1;
	c = -1;
	tmp = NULL;
	ret = cpy_matrix(args, 0);
	while (args[++i])
	{
		c = -1;
		while (args[i][++c])
		{
			if (args[i][c] == '*')
			{
				ret[i] = parse_files(args[i]);
				i = -1;
				while (ret[++i])
				{
					tmp = ft_strjoin(tmp, ret[i]);
					free(ret[i]);
					tmp = ft_strjoin(tmp, " ");
				}
				ret = ft_split(tmp, ' ');
				free(tmp);
				return (ret);
			}
		}
	}
	return (args);
}
