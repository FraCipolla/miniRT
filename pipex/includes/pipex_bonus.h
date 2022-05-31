#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_px
{
	int		f1;
	int		f2;
	int		status;
	int		n_cmd;
	int		**end;
	pid_t	*pid;
	char 	***mycmdargs;
	char	**mypath;
	char	*limiter;
	char	*here_doc_str;
	int		heredoc;
	int		*heredoc_pipe;
}	t_px;

char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int    init(int argc, char *argv[], char **envp, t_px *pipex);
void    create_pipes(t_px *px);
char	*get_next_line(int fd);
int		ft_strcmp(const char *s1, const char *s2);
void	here_doc_cmd(t_px *pipex);
void	here_doc_pipex(t_px *pipex);
int		msgerror(char *s1);

#endif