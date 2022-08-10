#include "header.h"

void	add_char(char **grid, int pos_y, int pos_x){
	grid[pos_y][pos_x] = 'X';
}

void	ft_print_grid(char **grid){
	int i = 0;
	int	c = 0;

	while (i < 19){
		c = 0;
		while (grid[i][c]){
			printf("%c", grid[i][c]);
			c++;
		}
		i++;
	}
}

void	lunch_game(){
	char	**grid;
	int i = -1;
	int c;

	grid = (char**)malloc(sizeof(char*) * 21);
	grid[20] = NULL;
	while (++i < 19){
		grid[i] = strdup("|                                                                    |\n");
	}
	grid[19] = strdup("oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo\n");
	//add_char(grid, 18, 35);
	ft_print_grid(grid);
	ft_loop(grid);
}
int main(int argc, char *argv[]){
	char	scan;

	printf("Welcome to this awsome game!\nType 's' to lunch the game:\n");
	scanf("%c", &scan);
	if (scan == 's')
		lunch_game();
	return (0);
}