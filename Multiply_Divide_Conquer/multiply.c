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

void add(int *ans, int ans_index, int *ans1, int len) {
    int i;

    for(i = len; i >= 0; i--, ans_index--) {
        ans[ans_index]   += ans1[i];
        ans[ans_index-1] += ans[ans_index]/10;
        ans[ans_index]    = ans[ans_index]%10;
    }
}

int *multiply(char *a, int a_len, char *b, int b_len, int *c, int skip) {
    int *ans = c;
    int i, j;
    int index;

    //printf("Len : %d : %d\n", a_len, b_len);

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

    return 0;
}

#define THRESHOLD 2 

int *divide_conquer_multiply(char *a, char *b, int skip) {
    int a_len = strlen(a);  
    int b_len = strlen(b);

    if (strlen(b) <= THRESHOLD) {
        int *ans = malloc((a_len + b_len) * sizeof(int));
        multiply(a, strlen(a), b, strlen(b), ans, skip);
        return ans;
    } else {
        int *ans  = malloc((a_len + b_len) * sizeof(int));
        int *ans1 = malloc((a_len + b_len/2) * sizeof(int));
        int *ans2 = malloc((a_len + b_len/2) * sizeof(int));

        multiply(a, strlen(a), b+strlen(b)/2, strlen(b)/2, ans2, 0);
        multiply(a, strlen(a), b, strlen(b)/2, ans1, 0);

        memset(ans, 0, (a_len + b_len) * sizeof(int));
        add(ans, a_len + b_len - 1, ans2, a_len + (b_len/2)-1);
        add(ans, a_len + b_len/2 - 1, ans1, a_len + (b_len/2)-1);
        
        return ans; 
    }

    /*
    printf("Multiplying : %s * %s = ", a, b); 
    print(_INT, ans, a_len + b_len);
    printf("\n");
    */
}

int main(int argc, char *argv[]) {
    int *c = divide_conquer_multiply(argv[1], argv[2], 0);

    printf("Multiplying : %s * %s = ", argv[1], argv[2]);
    print(_INT, c, strlen(argv[1]) + strlen(argv[2]));
    printf("\n");

    return 0;
}

