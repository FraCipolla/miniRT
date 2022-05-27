/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 17:12:52 by mcipolla          #+#    #+#             */
/*   Updated: 2022/05/27 16:34:25 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void    heredoc_child(t_px *pipex, char **envp, int i, char **cmdargs)
{
	char	*cmd;

	pipex->pid[i] = fork();
	if (pipex->pid[i] == 0)
	{
		dup2(pipex->end[i][0], STDIN_FILENO);
		close(pipex->end[i][0]);
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
		close(pipex->end[0][0]);
		close(pipex->end[0][1]);
	}
}

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
	if (px->heredoc == 1)
		heredoc_child(px, envp, i, px->mycmdargs[i]);
	else
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

int	msgerror(char *s1)
{
	printf("%s", s1);
	return (-1);
}

int main(int argc, char *argv[], char **envp)
{
	t_px	px;

	if (argc < 5)
		return (-1);
	if (init(argc, argv, envp, &px) == -1)
		return (-1);
	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		px.n_cmd -= 1;
		if (px.n_cmd < 2)
			return (msgerror("Need at least 2 commands"));
		px.limiter = argv[2];
		here_doc_pipex(&px);
		here_doc_cmd(&px);
		px.heredoc = 1;
	}
	else
	{
		px.f1 = open(argv[1], O_RDONLY);
		if (px.f1 < 0)
			return (-1);
	}
	create_pipes(&px);
	pipex(&px, envp);
	return (0);
}