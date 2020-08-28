#include <stdio.h>

void testGet(int *num) {
    *num = 3;
}

void _sum(int a, int b, int *c) {
    *c = a + b;
}

/*int _sum(int a, int b) {
    return a+b;
}*/

void main() {
    int a=0;

    testGet(&a);

    printf("%d \n", a);
    
    int b;
    _sum(1, 2, &b);
    printf("%d \n", b);
}