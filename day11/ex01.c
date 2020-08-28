#include <stdio.h>

int main() {
    int data = 0;
    int *p = &data;
    int **pp = &p;     //2차원
    int ***ppp = &pp;   //3차원

    data++;
    printf("%d \n", *p);

    data++;
    printf("%d \n", **pp);
    
    data++;
    printf("%d \n", ***ppp);


    return 0;
}