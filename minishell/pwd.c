/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 20:23:27 by mcipolla          #+#    #+#             */
/*   Updated: 2022/06/11 20:24:19 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_pwd(char *str)
{
	char	path[1000];
	int	i;
	char **tmp;

	i = 3;
	if (str[i] && str[i] != ' ')
	{
		tmp = ft_split(str, ' ');
		printf("zsh: command not found: %s\n", tmp[0]);
		return (0);
	}
	while (str[i])
	{
		if (str[i] != ' ')
		{
			printf("pwd: too many arguments\n");
			return (0);
		}
		i++;
	}
	getcwd(path, 1000);
	printf("%s\n", path);
	return (0);
}
