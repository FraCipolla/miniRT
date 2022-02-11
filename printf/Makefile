# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/02 15:37:04 by mcipolla          #+#    #+#              #
#    Updated: 2022/02/11 10:58:30 by mcipolla         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =  libftprintf.a
SRCS =  ft_printc.c ft_printdi.c ft_printp.c ft_prints.c ft_printxX.c ft_printf.c ft_utility.c ft_utility2.c ft_itoa.c ft_printu.c
OBJS =  $(SRCS:.c=.o)
FLAGS = -Wall -Wextra -Werror
LIBFT = libft.a
$(NAME):
		make -C libft
		cp libft/libft.a $(NAME)
		gcc -c $(FLAGS) $(SRCS)
		ar rc $(NAME) $(OBJS)
		ranlib $(NAME)
bonus: all
all:	$(NAME)
clean:
		rm -f $(OBJS)

fclean: clean
		rm -f $(NAME) $(LIBFT)
		make fclean -C libft

re:	fclean all
.PHONY: all clean fclean re