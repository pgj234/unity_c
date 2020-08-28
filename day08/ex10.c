#include <stdio.h>

void test(int _a[]) {
    int _tmp = _a[2];
    _a[2] = _a[0];
    _a[0] = _tmp;
}

void main() {
    int a[3] = {1, 2, 3};

    printf("%d %x \n", a[0], a);

    test(a);
    printf("%d %d %d \n", a[0], a[1], a[2]);
}