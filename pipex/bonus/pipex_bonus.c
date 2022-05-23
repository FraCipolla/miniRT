/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 17:12:52 by mcipolla          #+#    #+#             */
/*   Updated: 2022/05/23 14:53:29 by mcipolla         ###   ########.fr       */
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

void	close_pipes(t_px *pipex)
{
	int	i;

	i = 0;
	while (i < (2 * pipex->arg - 3) - 1)
	{
		close (pipex->end[i]);
		i++;
	}
}

void    child(t_px *pipex, char **envp, int i, char **cmdargs)
{
	char    *cmd;

	if (i == 0)
	{
		dup2(pipex->f1, STDIN_FILENO);
		dup2(pipex->end[1], STDOUT_FILENO);
		// close_pipes(pipex);
	}
	else if (i == pipex->arg - 4)
	{
		dup2(pipex->end[2 * i - 2], STDIN_FILENO);
		dup2(pipex->f2, STDOUT_FILENO);
		// close_pipes(pipex);
	}
	else
	{
		dup2(pipex->end[2 * i - 2], STDIN_FILENO);
		dup2(pipex->end[2 * i + 1], STDOUT_FILENO);
		// close_pipes(pipex);
	}
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

void    pipex(t_px *px, char **envp)
{
	int		i;
	char	**cmdargs;
	pid_t	pid;

	px->end = (int *)malloc(sizeof(int) * (2 * px->arg - 3) - 1);
	i = -1	;
	while (++i < px->arg - 3)
		pipe(px->end + i * 2);
	i = -1;
	while (++i < px->arg - 3)
	{
		pid = fork();
		if (pid < 0)
         	return (perror("Fork: "));
		if (pid == 0)
		{
			cmdargs = px->mycmdargs[i];
			child(px, envp, i, cmdargs);
			close_pipes(px);
		}
	}
	close_pipes(px);
	waitpid(-1, NULL, 0);
	i = 0;
	// while (i < px->arg - 3)
	// {
	// 	waitpid(px->child[i], NULL, 0);
	// 	i++;
	// }
}

int main(int argc, char *argv[], char **envp)
{
	t_px	px;
	int		i;
	int		j;

	if (argc < 5)
		return (-1);
	px.arg = argc;
	px.mycmdargs = malloc(sizeof(char **) * argc - 2);
	px.mycmdargs[argc - 3] = NULL;
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
	pipex(&px, envp);
	return (0);
}