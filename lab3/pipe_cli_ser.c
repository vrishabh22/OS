#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
void main()
{
	int pipe1fd[2],pipe2fd[2],r1,r2,pid,file,n;
	char buffer[1024],fname[50];
	r1=pipe(pipe1fd);
	r2=pipe(pipe2fd);
	if(r1==-1 || r2==-1)
	{
		printf("creating pipes failed\n");
		exit(-1);
	}
	else
	{
		pid=fork();
		if(pid==-1)
		{
			printf("fork() syscall failed\n");
			exit(-1);
		}
		else if(pid==0)
		{
			printf("In child proces... which acts as client\n");
			//pipe1 is in read only mode
			//pipe2 is in write ony mode
			close(pipe1fd[1]); //close write end of pipe1
			close(pipe2fd[0]); //close read end of pipe2
			dup(pipe1fd[0]);
			dup(pipe2fd[1]);
			printf("Enter filename to request\n");
			scanf("%s",fname);
			write(pipe2fd[1],fname,sizeof(fname));
			printf("Received response\n");
			while((n=read(pipe1fd[0],buffer,sizeof(buffer)))>0)
			{
				write(1,buffer,n);
			}
			close(pipe2fd[1]);
			close(pipe1fd[0]);
		}
		else
		{
			//acts as server
			printf("In parent process\n");
			//pipe1 in write only
			//pipe2 in read only
			close(pipe1fd[0]);
			close(pipe2fd[1]);
			dup(pipe1fd[1]);
			dup(pipe2fd[0]);
			printf("Waiting for request...\n");
			read(pipe2fd[0],fname,sizeof(fname));
			printf("received request for %s\n",fname);
			file=open(fname,O_RDONLY);
			if(file<0)
				write(pipe1fd[1],"File not found\n",15);
			else
			{
				while((n=read(file,buffer,sizeof(buffer)))>0)
				{
					write(pipe1fd[1],buffer,n);
				}
			}
			close(pipe1fd[1]);
			close(pipe2fd[0]);
		}
	}
}
