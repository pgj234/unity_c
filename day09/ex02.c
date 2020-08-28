#include <stdio.h>

void test(const int *_a, int * const _b) {
    // *_a = 11;
    //_b = a;
    printf("%d \n", *_a, *_b);
}

int main() {
    int a = 10;
    int b = 11;

    test(&a, &b);

    return 0;
}