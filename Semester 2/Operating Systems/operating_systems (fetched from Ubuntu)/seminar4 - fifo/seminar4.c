#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
	int a[] = {1,2,3,4};
	if(fork()==0)
	{
		int fw = open("seminar4fifo", O_WRONLY);
		a[0]+=a[1];
		write(fw, &a[0], sizeof(int));
		close(fw);
		exit(0);
	}
	a[2]+=a[3];
	int fr = open("seminar4fifo", O_RDONLY);
	read(fr, &a[0], sizeof(int));
	a[0]+=a[2];
	printf("Suma este %d\n", a[0]);
	close(fr);
	return 0;
}