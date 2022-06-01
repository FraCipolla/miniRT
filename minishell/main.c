#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	char	*buff;

	buff = readline("minishell");
	add_history();	
	printf("%s\n", buff);
	return (0);
}