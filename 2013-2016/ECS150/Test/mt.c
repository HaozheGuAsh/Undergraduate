#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main (int argc, char *argv[]) {
pid_t childpid = 0;
int i,n;
if (argc != 2) {
fprintf (stderr, "usage: %s processes\n", argv[0]);
return 1;
}
n = atoi(argv[1]);
for (i = 1; i < n; i++){
if (childpid == fork()){break;}
}

fprintf(stderr,"i: %d\nprocess ID %d\nparent ID: %d\nchild ID:%ld\n", i, getpid(), getppid(), childpid);

wait(NULL);


return 0;
}
