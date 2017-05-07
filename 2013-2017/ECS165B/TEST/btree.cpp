#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <algorithm>
#include <signal.h>
#include <sstream>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <iomanip>

#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include    <fcntl.h>
using namespace std;

void writefile()
{
	mode_t FILE_MODE = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	char    buf1[] = "111111111";
	char    buf2[] = "ASH";
  char    buf3[];
	int     fd;
  off_t offset=8;
	if ((fd = creat("file.test", FILE_MODE)) < 0)
		perror("creat error");


	if (write(fd, buf1, 10) != 10)
		perror("buf1 write error");

	if (lseek(fd, offset, SEEK_SET) == -1)
		perror("lseek error");

	if (write(fd, buf2, 10) != 10)
		perror("buf2 write error");

  if (write(fd, buf1, 10) != 10)
		perror("buf1 write error");
	if (lseek(fd, 0, SEEK_END) == -1)
		perror("lseek error");
	if (write(fd, "it's the end", 12) != 12)
		perror("buf2 write error");
   cout<<"ASH offset at"<<offset<<endl;
  if (lseek(fd, offset, SEEK_SET) == -1)
     perror("lseek error");
   
}
int main()
{
	writefile();
	

}