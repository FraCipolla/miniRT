/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 17:12:52 by mcipolla          #+#    #+#             */
/*   Updated: 2022/05/19 16:32:46 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

char    *command_path(char **envp)
{
	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
			return (*envp + 5);
		envp++;
	}
	return(NULL);
}

void    child_one(t_px *pipex, char **envp, int *end)
{
	int     i;
	char    *cmd;

	dup2(pipex->f1, STDIN_FILENO);
	dup2(end[1], STDOUT_FILENO);
	close(end[0]);
	i = 0;
	while (pipex->mypath[i])
	{
		cmd = ft_strjoin(pipex->mypath[i], *pipex->mycmdargs[0]);
		if (access(cmd, R_OK) == 0)
			execve(cmd, *pipex->mycmdargs, envp);
		else
			free(cmd);
		i++;
	}
}

void    child_n(t_px *pipex, char **envp, int i, char **cmdargs)
{
	char    *cmd;

	waitpid(-1, &pipex->status, 0);
	dup2(pipex->end[i - 1], STDIN_FILENO);
	dup2(pipex->end[i], STDOUT_FILENO);
	close(pipex->end[i]);
	i = 0;
	while (pipex->mypath[i])
	{
		cmd = ft_strjoin(pipex->mypath[i], cmdargs[0]);
		if (access(cmd, R_OK) == 0)
			execve(cmd, cmdargs, envp);
		else
			free(cmd);
		i++;
	}
}

void    child_last(t_px *pipex, char *argv[], char **envp, int *end)
{
	char    **mycmdargs;
	int     i;
	char    *cmd;

	waitpid(-1, &pipex->status, 0);
	dup2(end[0], 0);
	dup2(pipex->f2, STDOUT_FILENO);
	close(end[1]);
	mycmdargs = ft_split(argv[pipex->arg - 2], ' ');
	i = 0;
	while (pipex->mypath[i])
	{
		cmd = ft_strjoin(pipex->mypath[i], mycmdargs[0]);
		if (access(cmd, R_OK) == 0)
			break ;
		else
			free(cmd);
		i++;
	}
	execve(cmd, mycmdargs, envp);
}

void    pipex(t_px *px, char *argv[], char **envp)
{
	int		i;
	char	**cmdargs;

	px->end = malloc(sizeof(int) * px->arg - 3);
	pipe(px->end);
	px->child = malloc(sizeof(pid_t) * px->arg - 3);
	px->child[0] = fork();
	if (px->child[0] < 0)
		return (perror("Fork: "));
	if (px->child[0] == 0)
		child_one(px, envp, px->end);
	i = 0;
	while (++i < px->arg - 4)
	{
		px->child[i] = fork();
		if (px->child[i] < 0)
         	return (perror("Fork: "));
		if (px->child[i] == 0)
		{
			cmdargs = px->mycmdargs[i];
			child_n(px, envp, i, cmdargs);
		}
	}
	px->child[i] = fork();
	if (px->child[i] < 0)
		return (perror("Fork: "));
	if (px->child[i] == 0)
		child_last(px, argv, envp, px->end);
	while (i > 0)
	{
		close(px->end[i]);
		i--;
	}
	while (i++ < px->arg - 3)
		waitpid(px->child[i], &px->status, 0);
}

int main(int argc, char *argv[], char **envp)
{
	t_px	px;
	int		i;
	int		j;

	if (argc < 5)
		return (-1);
	px.arg = argc;
	px.mycmdargs = malloc(sizeof(char **) * argc - 3);
	px.mycmdargs[argc - 4] = NULL;
	px.mypath = ft_split(command_path(envp), ':');
	px.f1 = open(argv[1], O_RDONLY);
	px.f2 = open(argv[argc -1], O_CREAT | O_RDWR | O_TRUNC, 0000644);
	if (px.f1 < 0 || px.f2 < 0)
		return (-1);
	i  = 2;
	j = 0;
	while (i < argc - 2)
	{
		px.mycmdargs[j] = ft_split(argv[i], ' ');
		i++;
		j++;
	}
	i = -1;
	while (px.mypath[++i])
		px.mypath[i] = ft_strjoin(px.mypath[i], "/");
	pipex(&px, argv, envp);
	return (0);
}