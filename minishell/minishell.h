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

# define CGREEN "\033[0;32m"
# define RESET   "\001\e[0m\002"

char	**ft_split(char const *s, char c);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strcpy(char *s1, char *s2);
size_t	ft_strlen(const char *s);
char	*rem_char(char *str, int r);
int		check_quotes(char *str, int flag);
char	*quotes_resolve(char *str, int q);
int		check_semicolon(char *str, char **mypath);
int		check_strcmp(char *str, char **mypath);
int		my_env(char *str);
int		my_exp(char *str);

#endif