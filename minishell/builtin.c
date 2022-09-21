/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:30:43 by mcipolla          #+#    #+#             */
/*   Updated: 2022/09/21 15:31:15 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_builtin(char **cmd)
{
	int	fd;

	fd = check_redir(cmd);
	cmd = cut_red(cmd);
	if (strcmp(cmd[0], "cd") == 0)
		exit_value = my_cd(cmd);
	else if (strcmp(cmd[0], "export") == 0)
		exit_value = my_exp(cmd);
	else if (strcmp(cmd[0], "unset") == 0)
		exit_value = my_unset(cmd[1]);
	else if (strcmp(cmd[0], "echo") == 0)
		exit_value = my_echo(cmd, fd);
	else if (strncmp(cmd[0], "pwd", 3) == 0)
		exit_value = my_pwd(cmd);
	else if (strcmp(cmd[0], "env") == 0)
		exit_value = my_env(cmd);
	else
		printf("bash: %s: command not found\n", cmd[0]);
}

int	check_builtin(char *str)
{
	if (strcmp(str, "export") == 0
		|| strcmp(str, "cd") == 0
		|| strcmp(str, "unset") == 0
		|| strcmp(str, "echo") == 0
		|| strcmp(str, "env") == 0
		|| strcmp(str, "pwd") == 0
		|| strcmp(str, "exit") == 0)
		return (0);
	return (1);
}
