/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parentheses.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 21:24:05 by mcipolla          #+#    #+#             */
/*   Updated: 2022/10/04 16:27:03 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	between_parentheses(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '(')
		{
			while (str[++i])
			{
				if (str[i] == ')')
					return (0);
			}
		}
	}
	return (1);
}

int	logic_operator(char *buff)
{
	if (ft_strncmp(buff, "&&", 2) == 0 || ft_strncmp(buff, "||", 2) == 0)
		return (2);
	if (buff[0] == '|' || buff[0] == '&')
		return (1);
	return (0);
}

char	*fill_parentheses(char *buff, int i)
{
	int		flag;
	char	*read;
	int		c;

	flag = 0;
	c = i;
	while (buff[i])
	{
		if (buff[i] == '(')
			if (strchr(buff + i, ')') == NULL)
				flag++;
		i++;
	}
	while (flag > 0)
	{
		read = readline("> ");
		if (check_emptyline(buff + c + 1) != 0)
			buff = ft_strjoin(buff, ";");
		buff = ft_strjoin(buff, " ");
		buff = ft_strjoin(buff, read);
		if (strchr(read, ')') != NULL)
			flag--;
		free(read);
	}
	return (buff);
}

char	*check_empty_parentheses(char *buff)
{
	int		i;

	i = 0;
	while (buff[i] == ' ')
		i++;
	if (buff[i] != '(')
	{
		while (buff[i] && logic_operator(&buff[i]) == 0)
		{
			if (buff[i] == '(' || buff[i] == ')')
			{
				printf("syntax error near unexpected token '%c'\n", buff[i]);
				free(buff);
				return (NULL);
			}
			i++;
		}
		i += logic_operator(buff + i);
		while (buff[i] && buff[i] == ' ')
			i++;
	}
	return (fill_parentheses(buff, i));
}
