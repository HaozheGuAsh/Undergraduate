#include <unistd.h>
#include <stdlib.h>
#include<stdio.h>
#include <fcntl.h>
#include<string.h>
#include<sys/types.h>
const unsigned int BUFSIZE = 512;
int main()
{
int fd, n;
char buf[BUFSIZE];
char buf1[5];
strcpy(buf1,"asdfd");
fd = creat ("foo", 0644);

printf("fd is %d str is %s\n",fd,buf1);
write(fd,buf1,5);
lseek(fd,0,SEEK_SET);
//n = read(fd,buf,BUFSIZE);
//unlink ("foo");

while ((n = read(fd, buf, BUFSIZE)) > 0)
{
printf("ddd %s",buf);
write (1, buf, n);
}
write(1,buf1,5);
perror("Error is :");
printf("n is %d",n);
exit(0);
}
