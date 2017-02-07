#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
main()
{
pid_t p=fork();

if(p==0)
{
printf("child entry\n");
sleep(5);
printf("Child exit\n");

}
else
{
printf("parent entry\n");
//sleep(10);
exit(0);
}
}
