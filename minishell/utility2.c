/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 18:32:21 by mcipolla          #+#    #+#             */
/*   Updated: 2022/06/23 18:01:27 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ret_word(char *str)
{
	int		i;
	char	*ret;

	i = 0;
	ret = NULL;
	while (str[i] != ' ' && str[i])
		i++;
	ret = malloc(sizeof(char) * i + 1);
	ret[i] = '\0';
	i = 0;
	while (str[i] != ' ' && str[i])
	{
		ret[i] = str[i];
		i++;
	}
	return (ret);
}

char	*quotes_resolve(char *str, int q)
{
	char	*tmp;
	int		i;

	i = 0;
	while (str[i] != q)
		i++;
	if (q == 34)
		str = rem_char(str, 39);
	else if (q == 39)
		str = rem_char(str, 34);
	while (1)
	{
		tmp = readline("quote> ");
		str = ft_strjoin(str, "\n");
		str = ft_strjoin(str, tmp);
		if (check_quotes(ft_split(tmp, '\n'), q) == q)
		{
			while (*tmp != q)
				tmp++;
			tmp++;
			if (check_quotes(ft_split(tmp, '\n'), 0) > 0)
				q = check_quotes(ft_split(tmp, '\n'), q);
			else
				break ;
		}
	}
	return (str);
}

void	ft_increase_shlvl()
{
	extern char **environ;
	int			i;
	int			tmp;
	char		*cpy;

	i = -1;
	cpy = malloc(sizeof(char) * 7);
	while (environ[++i])
	{
		if (strncmp(environ[i], "SHLVL", 5) == 0)
		{
			cpy = strncpy(cpy, environ[i], 6);
			break;
		}
	}
	tmp = atoi(environ[i] + 6) + 1;
	environ[i] = ft_strjoin(cpy, ft_itoa(tmp));
	
}
