#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char** argv) {
    int fd, rows, cols, i;
    int** m;

    if(argc <= 1) {
        fprintf(stderr, "No input file specified");
        exit(1);
    }

    fd = open(argv[1], O_RDONLY);
    if(fd == -1) {
        perror("Failed to open input file");
        exit(1);
    }

    if(read(fd, &rows, sizeof(int)) <= 0) {
        perror("Could not read the number of rows");
        exit(1);
    }

    if(read(fd, &cols, sizeof(int)) <= 0) {
        perror("Could not read the number of columns");
        exit(1);
    }

    m = (int**)malloc(rows * sizeof(int*));
    for(i=0; i<rows; i++) {
        m[i] = (int*)malloc(cols * sizeof(int));
        read(fd, m[i], cols*sizeof(int));
        for(int j=0; j<cols; j++) {
            printf("%2d " , m[i][j]);
        }
        printf("\n");
    }
    for(i=0;i<rows;i++)
	free(m[i]);
    free(m);

    close(fd);
    return 0;
}
