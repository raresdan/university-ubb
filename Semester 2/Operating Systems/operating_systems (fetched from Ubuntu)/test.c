#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
	printf("Hello girls! Happy birthday!\n");
	printf("%d\n", argc);
	for(int i = 0; i < argc; i++)
		printf("%s\n", argv[i]);
	printf("Print ended successfully :)\n");

	//int n;
	//scanf("%d", &n);
	//printf("You entered: %d\n", n);

	if(argc != 2){
		printf("You have to enter 1 argument!\n");
		return 1;
	}

	FILE* f;
	f = fopen(argv[1], "r");
	int n, m;
	fscanf(f, "%d %d", &n, &m);
	printf("n = %d, m = %d\n", n, m);

	int** matrix;
	matrix = (int**)malloc(n*sizeof(int*));
	for (int i = 0; i < n; i++){
		matrix[i] = (int*)malloc(m*sizeof(int));
		for(int j = 0; j < m; j++)
			fscanf(f, "%d", &matrix[i][j]);
	}

	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++)
			printf("%d ", matrix[i][j]);
		printf("\n");
	}
	for(int i = 0; i < n; i++)
		free(matrix[i]);

	free(matrix);
	fclose(f);
	return 0;
}
