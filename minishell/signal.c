/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 14:23:37 by mcipolla          #+#    #+#             */
/*   Updated: 2022/09/29 14:57:23 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_global(int status)
{
	if (WIFEXITED(status) != 0)
	{
		g_exit = WEXITSTATUS(status);
	}
	else if (WIFSIGNALED(status) != 0 && WIFSIGNALED(status) == 1)
		g_exit = 130;
	else
		g_exit = 0;
}

void	action_in_process(int sig)
{
	printf("\n");
	(void)sig;
}

void	action(int sig)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void)sig;
}

void	clt_echo(char *str)
{
	char		**stty;
	extern char	**environ;
	int			pid;

	pid = fork();
	if (pid == 0)
	{
		stty = malloc(sizeof(char *) * 3);
		stty[0] = ft_strdup("stty");
		stty[1] = ft_strdup(str);
		stty[2] = NULL;
		execve("/bin/stty", stty, environ);
	}
	if (pid > 0)
		waitpid(-1, NULL, 0);
}