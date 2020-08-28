#include <stdio.h>

void main() {
    int a = 0x12345678;
    int *pA = &a;
    int *p8 = pA;
    char *pC = (char *)pA;

    printf("%x \n", *pA);
    printf("%x \n", *p8);
    printf("%x \n", *pC);
    printf("%x \n", *(pC+1));
    printf("%x \n", *(pC+2));
}