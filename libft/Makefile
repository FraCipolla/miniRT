name = libft.a
src = *.c
obj = $(src:.c=.o)

$(name):
		gcc -Wall -Werror -Wextra $(src)
		ar rc $(name) $(obj)
		runlib $(name)

clean:
		rm -f $(obj)

fclean:
		clean
		rm -f $(name)