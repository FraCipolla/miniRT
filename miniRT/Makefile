NAME = miniRT
CC = gcc
SRC = main.c utility.c ft_split.c ft_atof.c check.c primitives.c mlx_utility.c vec_op.c vec_op2.c lighting.c ray.c
MLX_FLAG = -l mlx -framework openGL -framework AppKit
# MLX_FLAG = -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
GNL_SRC = get_next_line.c get_next_line_utils.c
GNL_DIR = get_next_line
GNL = $(addprefix $(GNL_DIR)/, $(GNL_SRC))
OBJ = $(SRC) $(GNL)

%.o: %.c $(OBJ)
	$(CC) -Wall -Wextra -Werror -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(MLX_FLAG) -o $(NAME)

clean:
	rm -f $(NAME)

fclean: clean

all: $(NAME)

re: fclean all
