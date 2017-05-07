#include <unistd.h>
#include<stdio.h>
#include <stdlib.h>
#include <fcntl.h>
void fsort ()
{
int pfd[2], fd, nread;
char buf[512];
if (pipe (pfd) == -1)
exit(-1);
//switch (fork()) {
//case -1:
//exit(-1);

//if (dup2(pfd[0], 0) != 0)
//exit (-1);
//if ((dup2(pfd[1], 1)) != 1)
//exit(-1);
//if (close (pfd[0]) == -1 || close (pfd[1]) == -1)
//exit (-1);
//execlp ("sort", "sort", NULL);
//exit (-1);
//}
if ((fd = open ("/home//haozhe26/ECS150/Test/foo", 0)) == -1)
perror("not open");
while ((nread = read (fd, buf, sizeof(buf))) != 0) {
if (nread == -1)
exit (-1);
printf("buf is %s",buf);
if (write (pfd[1], buf, nread) == -1)
exit(-1);}
if (close (fd) == -1 || close (pfd[1]) == -1)
{
exit (-1);}
while((nread = read(pfd[0], buf, sizeof(buf))) != 0) {
if (nread == -1)
exit(-1);
if (write (1, buf, nread) == -1)
exit (-1);}
if (close (pfd[0]) == -1)
exit (-1);
}
int main()
{
fsort();
}
