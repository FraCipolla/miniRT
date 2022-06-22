NAME = minishell

SRC = main.c ft_split.c utility.c ft_strlen.c utility2.c builtin.c ft_strdup.c echo.c ft_itoa.c check.c pwd.c cd.c ft_strrchr.c
GNL = get_next_line.c get_next_line_utils.c
GNLDIR = GNL/
GNLPATH = $(addprefix $(GNLDIR), $(GNL))

FLAG = -Wall -Wextra -Werror -lreadline

$(NAME):
		gcc $(FLAG) $(SRC) $(GNLPATH) -o $(NAME)

clean:
		rm -f $(NAME)

fclean: clean

all: $(NAME)

re: fclean all