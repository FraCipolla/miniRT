#include "header.h"
#include <conio.h>

typedef struct{
	char	*my_pg;
	int		x;
}	pg;

char	*ft_moveright(char *pg){
	int	i = 0;

	while (i < 68){
		if (pg[i] == 'X'){
			pg[i] = ' ';
				if (pg[i + 1] == 'O'){
				printf("Oh, too bad, you died!");
				exit(0);
				}
			else{
				pg[i + 1] = 'X';
				return (pg);
			}
		}
		i++;
	}
	return (pg);
}

char	*ft_moveleft(char *pg){
	int	i = 2;

	while (i < 69){
		if (pg[i] == 'X'){
			pg[i] = ' ';
			if (pg[i - 1] == 'O'){
				printf("Oh, too bad, you died!");
				exit(0);
				}
			else{
				pg[i - 1] = 'X';
				return (pg);
			}
		}
		i++;
	}
	return (pg);
}

void	ft_print_empty(int x, int y){
	
	char	empty[72] = "|                                                                    |\n";
	char	*obstacle = (char*)malloc(sizeof(char) * 72);
	int		i = 0;
	int		c = 1;

	obstacle[0] = '|';
	while (c < 69){
		if (c == y)
			obstacle[c] = 'O';
		else
			obstacle[c] = ' ';
		c++;
	}
	obstacle[c] = '|';
	obstacle[c + 1] = '\n';
	while (i < 20){
		if (i == x)
			printf("%s", obstacle);
		else
			printf("%s", empty);
		i++;
	}
}

void	ft_enemy(char *pg){
	int	x = 0;
	
	for (int i = 0; i < 20; i++){
		sleep(0.5);
		ft_print_empty(x += 1, 14);
		printf("%s", pg);
	}
}

void	ft_loop(char **grid){
	pg	pg;
	int	key_code;
	pg.my_pg = (char*)malloc(sizeof(char) * 80);
	char	empty[72] = "|                                                                    |\n";
	pg.my_pg = strdup("|                                 X                                  |        \r");
	int	x = 0;

	if (fork() == 0)
		ft_enemy(pg.my_pg);
	while(1){
		if ( _kbhit())
			key_code = getch();
		if (key_code == 'd'){
			pg.my_pg = ft_moveright(pg.my_pg);
			printf("%s", pg.my_pg);
			key_code = 0;
		}
		if (key_code == 'a'){
			pg.my_pg = ft_moveleft(pg.my_pg);
			printf("%s", pg.my_pg);
			key_code = 0;
		}
	}

}