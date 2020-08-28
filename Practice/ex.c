#include <stdio.h>

int Sum(int a, int b) {
    return a+b;
}

void main() {
    int (*fp)(int, int) = Sum;
    int result = (*fp)(2, 3);

    printf("%d", result);
}