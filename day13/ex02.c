#include <stdio.h>

int Sum(int a, int b) {
    return a+b;
}

int Sub(int a, int b) {
    return a-b;
}

int main() {
    int (*p[2])(int, int);
    p[0] = Sum;
    p[1] = Sub;

    for (int i=0; i<2; i++) {
        printf("%d, \n", p[i](1, 2));
    }

    return 0;
}