/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 19:08:41 by mcipolla          #+#    #+#             */
/*   Updated: 2022/06/01 21:02:35 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_strcmp(char *str)
{
	char	path[1000];
	
	if (strcmp(str, "pwd") == 0)
		{
			getcwd(path, 100);
			printf("%s\n", path);
			return (0);
		}
	return (-1);
}

int main()
{
	char	*buff;

	while (1)
	{
		buff = readline(CGREEN "minishell: " RESET);
		if (strcmp(buff, "exit") == 0)
			break ;
		if (buff != NULL)
			add_history(buff);
		if (check_strcmp(buff) == -1)
			printf("zsh: command not found: %s\n", buff);
		free(buff);
	}
	return (0);
}