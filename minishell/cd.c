/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 17:09:04 by mcipolla          #+#    #+#             */
/*   Updated: 2022/06/16 17:30:37 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_cd(char *str)
{
	char	**tmp;
	int		i;
	char	path[1000];
	
	i = 0;
	tmp = ft_split(str, ' ');
	while (tmp[i])
		i++;
	if (i == 1)
	{
		getcwd(path, 1000);
		return (0);
	}
	if (tmp[1] && chdir(tmp[1]) == -1)
	{
		if (i > 2)
			return (printf("cd: too many arguments\n"));
		else
			return (printf("cd: no such file or directory: %s\n", tmp[1]));
	}
	else
		return (0);
	return (0);
}