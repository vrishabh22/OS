#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
main()
{

pid_t pro=fork();

if(pro==0)
{

int i, a=0,b=1,c;
printf("%d %d ",a,b);
for(i=1;i<=8;i++)
	{
		c=a+b;
		a=b;
		b=c;
		printf("%d ",c);
	
	
	}
}

else
{
printf("parent process\n");
wait(NULL);

}

}
