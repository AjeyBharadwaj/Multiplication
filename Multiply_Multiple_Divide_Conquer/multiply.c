#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define THRESHOLD 512

typedef enum{
    _INT,
    _STR
} datatype;

void print(datatype d, void *array, int len, char *start_msg, char *end_msg) {
    int i;
    int *ptr = (int *)array;

    printf("%s", start_msg);

    switch(d) {
        case _INT:
            for(i = 0; i < len; i++)
                printf("%d", ptr[i]);
            break;
        case _STR:
            printf("%s", (char *)ptr);
            break;
    }
    printf("%s", end_msg);
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
        print(_INT, ans, a_len+b_len, "", "");
        printf("\n");
        */
    }

    return 0;
}

int *divide_conquer_multiply(char *a, char *b, int skip) {
    int a_len = strlen(a);  
    int b_len = strlen(b);

    if (strlen(b) <= THRESHOLD) {
        int *ans = malloc((a_len + b_len) * sizeof(int));
        multiply(a, strlen(a), b, strlen(b), ans, skip);
        return ans;
    } else {
        int *ans  = malloc((a_len + b_len) * sizeof(int));
        int *ans1 = malloc((a_len + b_len)/2 * sizeof(int));
        int *ans2 = malloc((a_len + b_len)/2 * sizeof(int));
        int *ans3 = malloc((a_len + b_len)/2 * sizeof(int));
        int *ans4 = malloc((a_len + b_len)/2 * sizeof(int));

        multiply(a+a_len/2, a_len/2, b+b_len/2, b_len/2, ans1, 0);
        multiply(a,         a_len/2, b+b_len/2, b_len/2, ans2, 0);
        multiply(a+a_len/2, a_len/2, b        , b_len/2, ans3, 0);
        multiply(a,         a_len/2, b        , b_len/2, ans4, 0);

        memset(ans, 0, (a_len + b_len) * sizeof(int));

        add(ans, a_len   + b_len    , ans1, (a_len + b_len)/2);
        add(ans, a_len/2 + b_len    , ans2, (a_len + b_len)/2);
        add(ans, a_len   + b_len/2  , ans3, (a_len + b_len)/2);
        add(ans, a_len/2 + b_len/2  , ans4, (a_len + b_len)/2);

        return ans; 
    }
}

int main(int argc, char *argv[]) {
    int *c = divide_conquer_multiply(argv[1], argv[2], 0);

    printf("Multiplying : %s * %s = ", argv[1], argv[2]);
    print(_INT, c, strlen(argv[1]) + strlen(argv[2]), "", "");
    printf("\n");

    return 0;
}

