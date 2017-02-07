#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
main()
{
pid_t p=fork();
if(p>0)
{
printf("parent entry");
sleep(16);
printf("parent exit");
}
else{
sleep(10);
printf("child");
//exit(0);

}
}
