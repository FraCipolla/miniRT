#include "get_next_line.h"

int main()
{
	int	fd;

	fd = open("41_with_nl", O_RDONLY);

	printf("%s\n", get_next_line(fd));
	return (0);
}