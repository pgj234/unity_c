#include <stdio.h>
#include <malloc.h>

int main() {
    char *ptr;
    int *ptr2;

    ptr = (char *)malloc(1);
    //int ptr[2]
    ptr2 = (int *)malloc(sizeof(int)*2);

    ptr[0] = 10;

    printf("%d \n", ptr[0]);

    ptr2[0] = 12;
    ptr2[1] = 24;
    printf("%4d%4d\n", ptr2[0], ptr2[1]);

    free(ptr2);
    free(ptr);

    return 0;
}