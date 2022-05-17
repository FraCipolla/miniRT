NAME = pipex

SRC = pipex.c
UTIL = ft_strjoin.c ft_split.c ft_strlen.c ft_strncmp.c
SRC_DIR = mandatory/
UTIL_DIR = utility/
SRCPATH = $(addprefix $(SRC_DIR), $(SRC))
UTILPATH = $(addprefix $(UTIL_DIR), $(UTIL))
# OBJ = $(SRCPATH:.c=.o)

FLAG = -Wall -Wextra -Werror

$(NAME):
		gcc $(FLAG) $(SRCPATH) $(UTILPATH) -o $(NAME)

clean:
		rm -f $(NAME)

fclean: clean

all: $(NAME)

re: fclean all