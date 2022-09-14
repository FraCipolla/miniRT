NAME = minishell

SRC = main.c ft_split.c utility.c ft_strlen.c utility2.c redirUtils.c \
		builtin.c builtin2.c ft_strdup.c echo.c ft_itoa.c check.c pwd.c \
			cd.c ft_strrchr.c free.c utility3.c pipeline.c childs.c
GNL = get_next_line.c get_next_line_utils.c
GNLDIR = GNL/
GNLPATH = $(addprefix $(GNLDIR), $(GNL))

FLAG = -Wall -Wextra -Werror -g -lreadline -L/Users/$(USER)/.brew/opt/readline/lib 

$(NAME): 
		gcc $(FLAG) $(SRC) $(GNLPATH) -o $(NAME)

clean:
		rm -f $(NAME)

fclean: clean

all: $(NAME)

re: fclean all