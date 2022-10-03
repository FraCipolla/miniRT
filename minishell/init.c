/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 15:15:07 by mcipolla          #+#    #+#             */
/*   Updated: 2022/10/03 14:45:49 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_path()
{
	char	*path;
	char	**ret;
	int		i;

	i = -1;
	path = getenv("PATH");
	if (path == NULL)
	{
		return (NULL);
	}
	else
	{
		ret = ft_split(path, ':');
		while (ret[++i])
			ret[i] = ft_strjoin(ret[i], "/");
	}
	return (ret);
}

void	init()
{
	// extern char	**environ;
	// // clt_echo("-ctlecho");

	// environ = cpy_env(environ);
	signal(SIGINT, action);
	signal(SIGQUIT, SIG_IGN);
}