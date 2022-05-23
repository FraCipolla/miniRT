NAME = pipex

SRC = pipex.c
UTIL = ft_strjoin.c ft_split.c ft_strlen.c ft_strncmp.c
SRC_DIR = mandatory/
UTIL_DIR = utility/
SRCPATH = $(addprefix $(SRC_DIR), $(SRC))
UTILPATH = $(addprefix $(UTIL_DIR), $(UTIL))

BONUS_NAME = pipex_bonus

BONUS = pipex_bonus.c
UTIL = ft_strjoin.c ft_split.c ft_strlen.c ft_strncmp.c
BONUS_DIR = bonus/
UTIL_DIR = utility/
BONUSPATH = $(addprefix $(BONUS_DIR), $(BONUS))
UTILPATH = $(addprefix $(UTIL_DIR), $(UTIL))
# OBJ = $(SRCPATH:.c=.o)

FLAG = -Wall -Wextra -Werror -g

$(NAME):
		gcc $(FLAG) $(SRCPATH) $(UTILPATH) -o $(NAME)

$(BONUS_NAME):
		gcc $(FLAG) $(BONUSPATH) $(UTILPATH) -o $(BONUS_NAME)

clean:
		rm -f $(NAME) $(BONUS_NAME)

fclean: clean

all: $(NAME) $(BONUS_NAME)

re: fclean all