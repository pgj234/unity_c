#include <stdio.h>

int main() {
    int **pp;
    int data = 3;

    int *p;

    p = &data;
    pp = &p;

    printf("%d \n", **pp);
}