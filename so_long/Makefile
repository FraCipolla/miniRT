NAME = so_long
SRC = main.c read_file.c utility.c check.c open_images.c updates.c movement.c
FLAG = -Wall -Werror -Wextra -g
LIBFT = libft/libft.a
MLX_FLAG = -l mlx -framework openGL -framework AppKit

$(NAME):
			make re -C libft
			gcc $(SRC) -o $(NAME) $(LIBFT) $(MLX_FLAG)

all:	$(NAME)

clean:
			rm -f $(NAME)

fclean:	clean
			make fclean -C libft

re:		fclean all

.PHONY:	all clean fclean re