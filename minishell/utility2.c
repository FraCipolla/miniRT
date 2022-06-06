/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 18:32:21 by mcipolla          #+#    #+#             */
/*   Updated: 2022/06/06 18:33:56 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_semicolon(char *str, char **mypath)
{
	int		i;
	char	**cmds;

	cmds = ft_split(str, ';');
	if (cmds[0] == NULL)
		return (-1);
	else
	{
		i = 0;
		while (cmds[i])
		{
			if (check_strcmp(cmds[i], mypath) == -1)
				printf("zsh: command not found: %s\n", cmds[i]);
			i++;
		}
	}
	return (0);
}

int	check_quotes(char *str, int flag)
{
	int	i;
	int	count;
	int	count2;

	i = 0;
	count = 0;
	count2 = 0;
	while (str[i])
	{
		if (str[i] == 39)
			count++;
		if (str[i] == 34)
			count2++;
		i++;
	}
	if (count % 2 != 0 && flag != 34)
		return (39);
	else if (count2 % 2 != 0 && flag != 39)
		return (34);
	else
		return (0);
}

char	*quotes_resolve(char *str, int q)
{
	int		c;
	char	*tmp;
	int		i;

	i = -1;
	c = 0;
	while (1)
	{
		tmp = readline("quote> ");
		str = ft_strjoin(str, "\n");
		str = ft_strjoin(str, tmp);
		if (check_quotes(tmp, q) == q)
		{
			free (tmp);
			return (rem_char(str, q));
		}
		free(tmp);
	}
	return (str);
}