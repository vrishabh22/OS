#include<stdio.h>
#include<sys/types.h>
void main()
{
	pid_t pid=fork();
	//if(pid<0)
	//printf("not created");
	if(pid==0)
	printf("child created");
	else
	printf("parent");
}
