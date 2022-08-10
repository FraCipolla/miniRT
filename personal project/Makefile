NAME = run
SRC = main.c loop.c
FLAG = -I/usr/lib/x86_64-linux-gnu -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

$(NAME):
	g++ $(SRC) -o $(NAME) $(FLAG)

clean:
	rm -f $(NAME)

fclean: clean

re:	fclean $(NAME)