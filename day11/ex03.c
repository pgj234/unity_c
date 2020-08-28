#include <stdio.h>

int main() {
    int data = 3;
    int **pp;
    int my_ptr = (int)&data;

    pp = (int **)&my_ptr;

    // int portnum = 1000;
    // *((int *)1000) = 1;
    // *((char *)0x7000) = 1;

    printf("%d \n", **pp);
    (**pp)++;
    //(**pp) = 5;
    printf("%d \n", data);

    return 0;
}