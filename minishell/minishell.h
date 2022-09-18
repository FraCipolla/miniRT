/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 17:36:01 by mcipolla          #+#    #+#             */
/*   Updated: 2022/09/07 14:29:55 by mcipolla         ###   ########.fr       */
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

int	exit_value;

/* BUILT-IN */

int				ft_strrchr(const char *s, char c);
int				my_pwd(char **tmp);
int				my_echo(char **args, int fd);
int				my_env(char **tmp);
int				my_exp(char **tmp);
int				my_unset(char *str);
int				my_cd(char **tmp);

/* CHECKS */

int				check_redir(char **args);
int				check_pwd(char *str);
int				check_semicolon(char *str, char **mypath);
int				check_strcmp(char **cmd, char **mypath, int fd);
int				check_quotes(char **tmp, int flag);
char			*check_infile(char **args);
int				check_dot(char **cmd, char **environ);
int				check_empty_env(char *str);

char			*ft_addspaces(char *str);
extern void		rl_replace_line(const char *text, int clear_undo);
char			*get_next_line(int fd);
int				status(int n);
void			msg_exit(char *str);
char			*first_check(char *readline);
void			my_free(char **mypath);
char			**ft_split(char const *s, char c);
int				quote_str(const char *s);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strjoin(char *s1, char *s2);
int				ft_strcpy(char *s1, char *s2);
size_t			ft_strlen(const char *s);
char			*rem_char(char *str, int r);
char			**cut_red(char **args);
char			*quotes_resolve(char *str, int q);
char			*ret_word(char *str);
char			*infile(char **args);
char			*ft_strdup(const char *s1);
// int				check_redir(char **args);
char			**cpy_matrix(char **matrix, int offset);
void			ft_increase_shlvl(void);
char			*ft_itoa(int n);
char			*ft_malloc_strcpy(const char *s, int n);
void			*ft_calloc(size_t count, size_t size);
char			**remove_env(char **env, char *search);
char			**cpy_matrix(char **matrix, int offset);
char			**sort_env(char **env);
char			**add_env(char **env, char *str);
int				check_env_path(char *str, char **environ);
void			here_doc(char *limiter, int *end);
char			*manage_env(char *str);
void			clt_echo(char *str);
char			**remove_quotes(char **args);
char			*resolve_env(char *str, int j);
char			*get_env(char *str);
int				memcmp_aux(int i, char **args);
int				cut_red_aux(char **args);
int				check_redir_aux1(char **args, int i);
int				check_redir_aux2(char **args, int i);
void			pipex(int **end, char **pipes, int n_pipes);
void			make_fork(char **mypath, char **cmd);
char			**init();
void			action(int sig);
int				check_builtin(char *str);
void			exec_builtin(char **cmd);
void			split_exec(char **mypath, char **cmd);

#endif