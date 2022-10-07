/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:33:53 by mcipolla          #+#    #+#             */
/*   Updated: 2022/10/07 16:04:28 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc(char *limiter)
{
	char	*buff;
	char	*ret;
	int		end[2];

	ret = NULL;
	buff = NULL;
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
	dup2(end[0], 0);
	write (end[1], ret, ft_strlen(ret));
	close(end[1]);
	close(end[0]);
	free(ret);
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

void	here_doc_pipes(char	**args, int **end)
{
	char	*limiter;
	// int		end[2];
	char	*buff;
	char	*ret;

	limiter = get_limiter(args);
	if (limiter == NULL)
		return ;
	printf("entra\n");
	ret = NULL;
	buff = NULL;
	// close(*end[0]);
	// close(*end[1]);
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
		write (*end[1], ret, ft_strlen(ret));
	free(ret);
}
