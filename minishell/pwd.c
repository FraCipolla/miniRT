/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 20:23:27 by mcipolla          #+#    #+#             */
/*   Updated: 2022/06/17 15:50:34 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_pwd(char **tmp)
{
	char	path[1000];
	int	i;

	i = 0;
	if (strcmp(tmp[0], "pwd") != 0)
	{
		printf("zsh: command not found: %s\n", tmp[0]);
		return (0);
	}
	while (tmp[i])
		i++;
	if (i > 1)
	{
		printf("pwd: too many arguments\n");
		return (0);
	}
	getcwd(path, 1000);
	printf("%s\n", path);
	return (0);
	}
