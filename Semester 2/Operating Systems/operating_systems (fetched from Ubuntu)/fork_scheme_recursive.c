#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int f(int n)
{
	if(n>0)
	{
		int pid = fork();
		if(pid == 0)
		{
			printf("Child %d\n", n);
			f(n-1);
		}
		else
			wait(0);		
	}
	exit(0);
}

int main(int argc, char **argv)
{
	f(3);
	return 0;
}