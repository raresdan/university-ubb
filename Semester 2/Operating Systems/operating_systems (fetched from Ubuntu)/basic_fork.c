#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
	int pid = fork();
	if(pid == 0)
	{
		execlp("grep", "grep", "-E", "\\<mere\\>", "test.txt", NULL);
		printf("Child\n");
		exit(0);
	}
	else
	{
		printf("Parent\n");
		wait(0);
	}
	return 0;
}