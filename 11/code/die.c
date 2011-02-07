# include <stdio.h>
# include <stdlib.h>

void die(char *msg)
{
    fputs("laplace: error: ", stderr);
    fputs(msg, stderr);
    putc('\n', stderr);
    exit(1);
}
