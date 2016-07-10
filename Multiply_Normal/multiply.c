#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum{
    _INT,
    _STR
} datatype;

void print(datatype d, void *array, int len) {
    int i;
    int *ptr = (int *)array;

    switch(d) {
        case _INT:
            for(i = 0; i < len; i++)
                printf("%d", ptr[i]);
            break;
        case _STR:
            printf("%s", (char *)ptr);
            break;
    }
}

int *multiply(char *a, char *b) {
    int *ans;
    int a_len = strlen(a);
    int b_len = strlen(b);
    int i, j;
    int skip = 0, index;

    //printf("Len : %d : %d\n", a_len, b_len);

    ans = (int *) malloc ((a_len + b_len)*sizeof(int));
    memset(ans, 0, (a_len + b_len)*sizeof(int));
    
    for(i = b_len-1; i >= 0; i--, skip++) {
        index = (a_len + b_len - 1) - skip;
        for(j = a_len-1; j >= 0; j--) {
            ans[index--] += (b[i] - '0') * (a[j] - '0');
            ans[index] += ans[index+1]/10;
            ans[index+1] %= 10;
        }
        /* 
        printf("Iterations : %d : ", i);
        print(_INT, ans, a_len+b_len);
        printf("\n");
        */
    }

    printf("Multiplying : %s * %s = ", a, b);
    print(_INT, ans, a_len + b_len);
    printf("\n");

    return 0;
}

int main(int argc, char *argv[]) {
    multiply(argv[1], argv[2]);

    return 0;
}

