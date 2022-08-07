NAME = miniRT
SRC = main.c utility.c ft_split.c ft_atof.c check.c primitives.c
FLAGS = -Wall -Werror -Wextra
MLX_FLAG = -l mlx -framework openGL -framework AppKit
GNL = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

$(NAME):
	gcc $(FLAGS) $(MLX_FLAG) $(SRC) $(GNL) -o $(NAME)

clean:
	rm -f $(NAME)

fclean: clean

all: $(NAME)

re: fclean all