NAME = minishell

SRC = main.c

FLAG = -Wall -Wextra -Werror -g -lreadline

$(NAME):
		gcc $(FLAG) $(SRC) -o $(NAME)

clean:
		rm -f $(NAME)

fclean: clean

all: $(NAME)

re: fclean all