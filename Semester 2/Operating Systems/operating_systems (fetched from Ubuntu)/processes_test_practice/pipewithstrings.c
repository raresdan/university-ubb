#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main()
{
	int pidA, pidB;
	char string[100];

	int p2a[2];
	pipe(p2a);

	int a2b[2];
	pipe(a2b);

	int b2p[2];
	pipe(b2p);

	pidA = fork();
	if(pidA == 0)
	{
		close(b2p[0]);
		close(b2p[1]);
		close(a2b[0]);
		close(p2a[1]);
		
		while(1)
		{
			if(read(p2a[0], &string,sizeof(string)) <= 0)
				break;
			if(strcmp(string,"stop") == 0)
				break;

			printf("Enter string: ");
        	scanf("%s", string);
			printf("Child A: %s\n", string);
			
			write(a2b[1],&string,sizeof(string));
		}
		close(p2a[0]);
		close(a2b[0]);
		exit(0);
	}
	pidB = fork();
	if(pidB == 0)
	{
		close(p2a[0]);
		close(p2a[1]);
		close(a2b[1]);
		close(b2p[0]);
		
		while(1)
		{
			if(read(a2b[0],&string,sizeof(string)) <= 0)
				break;
			if(strcmp(string,"stop") == 0)
				break;
			printf("Enter string: ");
       		scanf("%s", string);
			printf("Child B: %s\n", string);
			
			write(b2p[1], &string,sizeof(string));
		}
		close(a2b[0]);
		close(b2p[1]);
		exit(0);
	}

    printf("Enter string: ");
    scanf("%s\n", string);
    printf("Parent: %s\n", string);
    
    write(p2a[1], &string, sizeof(string));

    close(a2b[0]);
    close(a2b[1]);
    close(b2p[1]);
    close(p2a[0]);
    
    while (1)
    {
        if (read(b2p[0], &string, sizeof(string)) <= 0)
            break;
        if (strcmp(string, "stop") == 0)
            break;
        printf("Enter string: ");
        scanf("%s", string);
        printf("Parent: %s\n", string);
        
        write(p2a[1], &string, sizeof(string));
    }
    close(b2p[0]);
    close(p2a[1]);
    wait(0);
    wait(0);
		
}
