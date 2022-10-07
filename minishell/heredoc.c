/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:33:53 by mcipolla          #+#    #+#             */
/*   Updated: 2022/10/07 11:41:03 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc(char *limiter)
{
	char	*buff;
	char	*ret;
	int		end[2];

	ret = NULL;
	pipe(end);
	while (1)
	{
		buff = readline("> ");
		if (strcmp(buff, limiter) == 0)
			break ;
		ret = ft_strjoin(ret, buff);
		ret = ft_strjoin(ret, "\n");
		free(buff);
	}
	if (ret)
	{
		write (end[1], ret, ft_strlen(ret));
		dup2(end[0], 0);
	}
	close(end[1]);
	free(ret);
	close(end[0]);
	free(buff);
}

char	*get_limiter(char **args)
{
	int		i;
	char	*ret;

	i = 0;
	ret = NULL;
	while (args[i])
	{
		if (ft_strcmp(args[i], "<<") == 0)
			ret = args[i + 1];
		i++;
	}
	return (ret);
}

int	here_doc_pipes(char	**args)
{
	char	*limiter;
	int		end[2];
	char	*buff;
	char	*ret;

	limiter = get_limiter(args);
	if (limiter == NULL)
		return (-1);
	pipe(end);
	ret = NULL;
	while (1)
	{
		buff = readline("> ");
		if (strcmp(buff, limiter) == 0)
			break ;
		ret = ft_strjoin(ret, buff);
		ret = ft_strjoin(ret, "\n");
		free(buff);
	}
	free(buff);
	if (ret)
	{
		close(end[1]);
		write (end[0], ret, ft_strlen(ret));
		free(ret);
		return (end[0]);
	}
	free(ret);
	return (-1);
}
