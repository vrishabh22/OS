#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
void main()
{
	int pfds[2],pid,re;
	re=pipe(pfds);
	if(re==-1)
	{
		printf("Error in pipe() syscall\n");
		exit(0);
	}
	else
	{
		pid=fork();
		if(pid==-1)
		{
			printf("error in fork() syscall\n");
			exit(0);
		}
		else if(pid==0)
		{
			//child process
			close(1); //close standard output
			dup(pfds[1]);
			close(pfds[0]);
			execlp("ls","ls",NULL);
		}
		else
		{
			//parent process
			close(0);
			dup(pfds[0]);
			close(pfds[1]);
			execlp("wc","wc","-l",NULL);
		}
	}
}
