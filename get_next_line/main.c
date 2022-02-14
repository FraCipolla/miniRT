#include "get_next_line.h"

int main()
{
	int	fd;

	fd = open("42_with_nl", O_RDONLY);

	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	return (0);
}