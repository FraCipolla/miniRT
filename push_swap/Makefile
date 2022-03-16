# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/16 00:24:25 by mcipolla          #+#    #+#              #
#    Updated: 2022/03/16 00:24:27 by mcipolla         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap
SRC = checker.c main.c swap.c push.c rotate.c rev_rotate.c utility.c find.c findcomb.c
OBJ = $(SRC:.c=.o)
FLAG = -Wall -Werror -Wextra -g
LIBFT = libft/libft.a

$(NAME):
		make re -C libft
		gcc $(FLAG) -o $(NAME) $(SRC) $(LIBFT)

all:	$(NAME)

clean:
		rm -f $(OBJ)

fclean:	clean
		rm -f $(NAME) $(LIB)
		make fclean -C libft

re:		fclean all

.PHONY:	all clean fclean re