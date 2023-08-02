#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main()
{
	char string[100];
	int a2b, c2a;
	a2b = open("a2b", O_WRONLY);
	c2a = open("c2a", O_RDONLY);

	while(1)
	{   
		printf("Enter string: ");
	    scanf("%s", string);
	    printf("A: %s", string);

		write(a2b, &string, sizeof(string));
		     
		if(read(c2a,&string,sizeof(string))<=0)
			break;
		if(strcmp(string,"stop") == 0)
			break;

		printf("Enter string: ");
		scanf("%s", string);
		printf("A: %s", string);

		write(a2b,&string,sizeof(string));
	}
	close(a2b);
	close(c2a);
}
