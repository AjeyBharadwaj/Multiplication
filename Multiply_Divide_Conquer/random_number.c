#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int i, j;
    srand(time(NULL));

    for(i = 1; i < 3; i++) {
        for(j = 0; j < atoi(argv[i]); j++)
            printf("%d", rand()%10);
        printf(" ");
    }
    printf("\n");
    return 0;
}

