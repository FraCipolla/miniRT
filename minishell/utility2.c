/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 18:32:21 by mcipolla          #+#    #+#             */
/*   Updated: 2022/10/01 14:15:58 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_chars(char c)
{
	if (c && c != ' ' && c != '"'
		&& c != '\'' && c != '\n')
		return (0);
	return (1);
}

void	add_char(char **toret, char a)
{
	char aux[2];

	aux[0] = a;
	aux[1] = 0;
	*toret = ft_strjoin(*toret, aux);
}

void	ft_increase_shlvl(void)
{
	extern char	**environ;
	char		*nb;
	int			tmp;
	char		*cpy;

	tmp = -1;
	nb = NULL;
	cpy = ft_strdup("SHLVL=");
	while (environ[++tmp])
	{
		if (strncmp(environ[tmp], "SHLVL", 5) == 0)
		{
			tmp = atoi(environ[tmp] + 6) + 1;
			nb = ft_itoa(tmp);
			environ[tmp] = ft_strjoin(cpy, nb);
			break ;
		}
	}
	free(cpy);
	if (nb != NULL)
		free(nb);
}

void	msg_exit()
{
	printf ("\e[A\e[K");
	printf("minishell: exit\n");
	exit(0);
}

char	**cpy_matrix(char **matrix, int offset)
{
	int		i;
	char	**ret;

	i = 0;
	while (matrix[i])
		i++;
	ret = (char **)malloc(sizeof(char *) * (i - offset));
	i = 0;
	while (matrix[i])
	{
		ret[i] = matrix[i];
		i++;
	}
	ret[i] = NULL;
	return (ret);
}
