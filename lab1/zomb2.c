#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
int main()
{





	pid_t p;
	p=fork();
	if(p>0)
	{	
		printf("parent entry");
		//wait(NULL);
		sleep(15);
		printf("parent exit");
	}
	

	else
	{
		printf("child entry");
		exit(0);
		printf("child exit");
	}
	return 0;
}