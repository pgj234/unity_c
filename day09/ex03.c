#include <stdio.h>

int main() {
    char *p1 = (char *)100; //1
    short *p2 = (short *)100;//2
    int *p3 = (int *)100;  //4

    p1++;
    p2++;
    p3++;

    printf("%d, %d, %d \n", p1, p2, p3);
}