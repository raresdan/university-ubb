#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv)
{	
	for(int i=0; i<3; i++)
	{
		int pid = fork();
		if(pid == 0)
		{
			for(int j = 0; j<3;j++)
			{
				int pjd = fork();
				if(pjd == 0)
				{
					printf("Child %d %d\n", i,j);
					exit(0);
				}
			}
			for(int j = 0; j<3; j++)
				wait(0);
			exit(0);	
		}
	}

	for(int i = 0; i<3; i++)
		wait(0);



	return 0;
}