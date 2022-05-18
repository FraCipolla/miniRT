#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <string.h>

static char    *rl_gets (char *str)
{
    static char *line;
  /* If the buffer has already been allocated, return the memory
     to the free pool. */
  if (line)
    {
      free (line);
      line = (char *)NULL;
    }

  /* Get a line from the user. */
  line = readline ("");

  strcpy(str, line);
  free (line);

  return (str);
}

int main(int argc, char *argv[])
{
    char *str;
    rl_gets(str);
    return (0);
}