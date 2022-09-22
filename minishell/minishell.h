/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 17:36:01 by mcipolla          #+#    #+#             */
/*   Updated: 2022/09/22 18:05:38 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <dirent.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>
# include "readline/readline.h"

int	g_exit;

/* READLINE */

extern void		rl_replace_line(const char *text, int clear_undo);
void			rl_redisplay (void);

/* BUILT-IN */

int				my_pwd(char **tmp);
int				my_echo(char **args, int fd);
int				my_env(char **tmp);
int				my_exp(char **tmp);
int				my_unset(char *str);
int				my_cd(char **tmp);

/* BUILT-IN UTILITY */

char			**sort_env(char **env);
char			**add_env(char **env, char *str);
int				check_empty_env(char *str);
int				check_pwd(char *str);
void			ft_increase_shlvl(void);

/* CHECKS */

int				check_redir(char **args);
int				check_semicolon(char *str, char **mypath);
int				check_strcmp(char **cmd, char **mypath, int fd);
char			*check_infile(char **args);
int				check_dot(char **cmd, char **environ);
int				check_builtin(char *str);
char			**check_wild(char **args);

/* UTILITY */

int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strjoin(char *s1, char *s2);
int				ft_strcpy(char *s1, char *s2);
size_t			ft_strlen(const char *s);
char			**ft_split(char const *s, char c);
char			*ft_strdup(const char *s1);
char			*ft_itoa(int n);
char			*ft_malloc_strcpy(const char *s, int n);
void			*ft_calloc(size_t count, size_t size);
char			**cpy_matrix(char **matrix, int offset);
int				ft_strrchr(const char *s, char c);
char			*get_next_line(int fd);

/* PIPES/HEREDOC/REDIRECTION */

void			pipex(int **end, char **pipes, int n_pipes);
int				here_doc_pipes(char	**args);
void			here_doc(char *limiter, int *end);
char			**cut_red(char **args);
char			*infile(char **args);

/* STRINGS OPERATIONS */

char			*ft_addspaces(char *str);
int				check_env_path(char *str, char **environ);
char			**remove_quotes(char **args);
char			*resolve_env(char *str, int j);
char			*get_env(char *str);
char			*rem_char(char *str, int r);
char			**remove_env(char **env, char *search);

/* PROGRAM BEHAVIOUR */

void			clt_echo(char *str);
void			make_fork(char **mypath, char **cmd);
char			**init();
void			action(int sig);
void			exec_builtin(char **cmd);
void			split_exec(char **mypath, char **cmd);
void			my_free(char **mypath);
void			last_free(char **m1, char **m2, char *str);
void			msg_exit();

/* WILDCARD */

char	*parse_files();

#endif