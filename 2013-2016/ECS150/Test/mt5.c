#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
static void charatatime (char *);
int main (void)
{
int pid = fork();
if (pid == 0) {
charatatime ("output from child\n");
}
else {
charatatime ("output from parent\n");
}
exit(0);
}
static void charatatime (char *str) {
char *ptr;
char c;
setbuf (stdout, NULL);
for (ptr = str; c = *ptr++;)
putc (c, stdout);
}
