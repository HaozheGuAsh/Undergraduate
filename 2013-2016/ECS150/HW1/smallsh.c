#include "smallsh.h" /* include file for example */
#include <stdlib.h>
#include<signal.h>
#include<sys/wait.h>

/* program buffers and work pointers */
static char inpbuf[MAXBUF], tokbuf[2*MAXBUF], *ptr = inpbuf, *tok = tokbuf;
//static struct sigaction oacti,oactq;
void f_action(int);
int curchild,notkill;
userin(p) /* print prompt and read a line */
char *p;
{
  int c, count;
  /* initialization for later routines */
  ptr = inpbuf;
  tok = tokbuf;

  /* display prompt */
  printf("%s ", p);

  for(count = 0;;){
    if((c = getchar()) == EOF)
      return(EOF);

    if(count < MAXBUF)
      inpbuf[count++] = c;

    if(c == '\n' && count < MAXBUF){
      inpbuf[count] = '\0';
      return(count);
    }

    /* if line too long restart */
    if(c == '\n'){
      printf("smallsh: input line too long\n");
      count = 0;
      printf("%s ", p);
    }
  }
}

static char special[] = {' ', '\t', '&', ';', '\n', '\0'};

inarg(c) /* are we in an ordinary argument */
char c;
{
  char *wrk;
  for(wrk = special; *wrk != '\0'; wrk++)
    if(c == *wrk)
      return(0);

  return(1);
}

gettok(outptr) /* get token and place into tokbuf */
char **outptr;
{
  int type;

  *outptr = tok;

  /* strip white space */
  for(;*ptr == ' ' || *ptr == '\t'; ptr++)
    ;

  *tok++ = *ptr;

  switch(*ptr++){
    case '\n':
      type = EOL; break;
    case '&':
      type = AMPERSAND; break;
    case ';':
      type = SEMICOLON; break;
    default:
      type = ARG;
      while(inarg(*ptr))
        *tok++ = *ptr++;
  }

  *tok++ = '\0';
  return(type);
}

/* execute a command with optional wait */
runcommand(cline, where)
char **cline;
int where;
{
  int ppid,pid,exitstat, ret;

  if((pid = fork()) < 0)
  {
    perror("smallsh");
    return(-1);
  }
  
 // printf("fork pid is %d\n",pid);
  if(pid>0&where==FOREGROUND){curchild=pid;/*printf("foreground pid %d\n",curchild);*/}
  if(pid == 0)
  {
  // if(where==FOREGROUND)
  // {
  //  printf("forehead pid %d\n",getpid());
//    void fore_action(int);   
//    static struct sigaction fact; 
//    fact.sa_handler=SIG_IGN;
//    sigaction(SIGINT,&fact,NULL);
//    sigaction(SIGQUIT,&fact,NULL);
 //   if(where==FOREGROUND){curchild=getpid();printf("foreground pid %d\n",curchild);}
 //   pr
    execvp(*cline, cline);
  //  printf("back\n");
    perror(*cline);
    exit(127);
  }
  if(where==FOREGROUND)
  {
 // 	printf("creat follow!\n");
	if((ppid=fork())==0)
  	{
	  int status;
    	  static struct sigaction fact;
    	  fact.sa_handler=f_action;
    	  sigaction(SIGINT,&fact,NULL);
    	  sigaction(SIGQUIT,&fact,NULL);
    	  while(1)
	  {
	    if(curchild==0){/*printf("i can end\n");*/exit(0);}
	  }	
  	}
  }
  /* code for parent */
  /* if background process print pid and exit */
  if(where == BACKGROUND){
    printf("[Process id %d]\n", pid);
   // void back_action(int);   
//    static struct sigaction bact; 
  //  bact.sa_handler=SIG_IGN;
   // sigaction(SIGINT,&bact,NULL);
   // sigaction(SIGQUIT,&bact,NULL);
    return(0);
  }

  /* wait until process pid exits */
  while( (ret=wait(&exitstat)) != pid && ret != -1)
    ;

  return(ret == -1 ? -1 : exitstat);
}

procline() /* process input line */
{
  char *arg[MAXARG+1]; /* pointer array for runcommand */
  int toktype; /* type of token in command */
  int narg; /* numer of arguments so far */
  int type; /* FOREGROUND or BACKGROUND? */

  for(narg = 0;;){ /* loop forever */
    /* take action according to token type */
    //printf("...%s\n",arg[narg]);
    switch(toktype = gettok(&arg[narg])){
      case ARG:
        if(narg < MAXARG)
          narg++;
        break;

      case EOL:
      case SEMICOLON:
      case AMPERSAND:
        type = (toktype == AMPERSAND) ? BACKGROUND : FOREGROUND;
        if(narg != 0){
          arg[narg] = NULL;
          runcommand(arg, type);
        }
        
        if(toktype == EOL)
          return;

        narg = 0;
        break;
    }
  }
}

char *prompt = "Command>"; /* prompt */
main()
{
  void shell_action(int);
  static struct sigaction sact;
  sact.sa_handler=SIG_IGN; 
  sigaction(SIGINT,&sact,NULL);
  sigaction(SIGQUIT,&sact,NULL);
 // printf("shell pid is %d\n",getpid());
  while(userin(prompt) != EOF)
    procline();
}
void f_action(int sig)
{
  char dummy;
//  printf("shell pid is %d\n",getpid());
 // printf("currentchild pid is %d\n",curchild);
 // printf("got sigint or sigquit\n");
 // printf("send to child process %d\n",curchild);
 // fprintf(stdout,"in handler\n,curchild is %d,my id is %d",curchild,getpid());
  if(curchild>0)
  {
   fprintf(stdout,"Confirm killing process %d ?(type y to kill)",curchild);
   scanf("%c",&dummy);
   if(dummy=='y')
   {
     kill(curchild,SIGKILL);
     curchild=0;
   }
  }
}
/*void fore_action(int sig)
{
  printf("got signal to foreground\n");
  printf("do u really want to kill %d?\n",getpid());
}
void back_action(int sig)
{
  printf("got signal to background\n");
  printf("do u really want to kill %d?\n",getpid());
}*/
