/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 17:12:52 by mcipolla          #+#    #+#             */
/*   Updated: 2022/05/27 12:24:01 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void    child_1(t_px *pipex, char **envp, int i, char **cmdargs)
{
	char	*cmd;

	pipex->pid[i] = fork();
	if (pipex->pid[i] == 0)
	{
		close(pipex->end[i][0]);
		dup2(pipex->f1, STDIN_FILENO);
		dup2(pipex->end[i][1], STDOUT_FILENO);
		close(pipex->end[i][1]);
		i = 0;
		while (pipex->mypath[i])
		{
			cmd = ft_strjoin(pipex->mypath[i], cmdargs[0]);
			if (access(cmd, R_OK) == 0)
				break ;
			else
				free(cmd);
			i++;
		}
		execve(cmd, cmdargs, envp);
	}
	else
	{
		close(pipex->f1);
		close(pipex->end[0][1]);
	}
}

void    child_mid(t_px *pipex, char **envp, int i, char **cmdargs)
{
	char	*cmd;

	pipex->pid[i] = fork();
	if (pipex->pid[i] == 0)
	{
		close(pipex->end[i][0]);
		dup2(pipex->end[i - 1][0], STDIN_FILENO);
		dup2(pipex->end[i][1], STDOUT_FILENO);
		close(pipex->end[i - 1][0]);
		close(pipex->end[i][1]);
		i = 0;
		while (pipex->mypath[i])
		{
			cmd = ft_strjoin(pipex->mypath[i], cmdargs[0]);
			if (access(cmd, R_OK) == 0)
				break ;
			else
				free(cmd);
			i++;
		}
		execve(cmd, cmdargs, envp);
	}
	else
	{
		close(pipex->end[i - 1][0]);
		close(pipex->end[i][1]);
	}
}

void    child_last(t_px *pipex, char **envp, int i, char **cmdargs)
{
	char	*cmd;

	pipex->pid[i] = fork();
	if (pipex->pid[i] == 0)
	{
		close(pipex->end[i - 1][1]);
		dup2(pipex->end[i - 1][0], STDIN_FILENO);
		dup2(pipex->f2, STDOUT_FILENO);
		close(pipex->end[i - 1][0]);
		close(pipex->f2);
		i = 0;
		while (pipex->mypath[i])
		{
			cmd = ft_strjoin(pipex->mypath[i], cmdargs[0]);
			if (access(cmd, R_OK) == 0)
				break ;
			else
				free(cmd);
			i++;
		}
		execve(cmd, cmdargs, envp);
	}
	else
	{
		close(pipex->f2);
		close(pipex->end[i - 1][0]);
	}
}

void    pipex(t_px *px, char **envp)
{
	int	i;
	int	status;

	i = 0;
	child_1(px, envp, i, px->mycmdargs[i]);
	while (++i < px->n_cmd - 1)
	{
		child_mid(px, envp, i, px->mycmdargs[i]);
	}
	child_last(px, envp, i, px->mycmdargs[i]);
	i = -1;
	while (++i < px->n_cmd)
		waitpid(px->pid[i], &status, 0);
}

void	here_doc_pipex(t_px *pipex)
{
	char	*buff;

	buff = NULL;
	write(1, "> ", 2);
	while (1)
	{
		buff = get_next_line(0);
		if (ft_strcmp(buff, pipex->limiter) == 0)
			break;
		write(1, "> ", 2);
	}
}

int main(int argc, char *argv[], char **envp)
{
	t_px	px;

	if (argc < 5)
		return (-1);
	init(argc, argv, envp, &px);
	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		px.limiter = argv[2];
		here_doc_pipex(&px);
		return (0);
	}
	px.f1 = open(argv[1], O_RDONLY);
	if (px.f1 < 0 || px.f2 < 0)
		return (-1);
	create_pipes(&px);
	pipex(&px, envp);
	return (0);
}