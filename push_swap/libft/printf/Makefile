# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/11 17:28:59 by mcipolla          #+#    #+#              #
#    Updated: 2022/05/11 17:28:59 by mcipolla         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = printf.a
SRCS = ft_char.c ft_number.c ft_printf.c ft_utility.c
OBJ = $(SRCS:.c=.o)
FLAGS =	-Wall -Wextra -Werror

$(NAME):
		gcc $(FLAGS) -c $(SRCS)

clean:
		rm -f $(OBJ)

fclean:	clean

re:		fclean
		$(NAME)

.PHONY: clean fclean re