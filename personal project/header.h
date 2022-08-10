#ifndef HEADER_H
#define	HEADER_H

# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>
# include <SDL2/SDL_ttf.h>
# include <SDL2/SDL_mixer.h>

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <malloc.h>

void	ft_loop(char **grid);
void	ft_print_grid(char **grid);

#endif