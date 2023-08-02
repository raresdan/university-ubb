#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main()
{
	char string[100];
	int b2c, a2b;
	b2c = open("b2c", O_WRONLY);
	a2b = open("a2b", O_RDONLY);

	while(1)
	{
		if(read(a2b,&string,sizeof(string))<=0)
			break;
		if(strcmp(string,"stop") == 0)
			break;

		printf("Enter string: ");
		scanf("%s", string);
		printf("A: %s\n", string);

		write(b2c,&string,sizeof(string));
	}
	close(a2b);
	close(b2c);
}
