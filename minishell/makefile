NAME = minishell

SRC = main.c ft_split.c utility.c ft_strlen.c utility2.c builtin.c ft_strdup.c echo.c ft_itoa.c check.c pwd.c cd.c

FLAG = -Wall -Wextra -Werror -g -lreadline

$(NAME):
		gcc $(FLAG) $(SRC) -o $(NAME)

clean:
		rm -f $(NAME)

fclean: clean

all: $(NAME)

re: fclean all