/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 18:32:21 by mcipolla          #+#    #+#             */
/*   Updated: 2022/09/21 15:44:18 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_increase_shlvl(void)
{
	extern char	**environ;
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
			break ;
		}
	}
	tmp = atoi(environ[i] + 6) + 1;
	environ[i] = ft_strjoin(cpy, ft_itoa(tmp));
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
