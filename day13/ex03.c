#include <stdio.h>

void MyAbsolute(int *p) {
    if (*p < 0) {
        *p = (*p)* -1;
    }
}

int SumABS(int a, int b, void (*fp_abs)(int *)) {
    // if (a < 0) {
    //     a = 0 -a;
    // }

    // if (b < 0) {
    //     b = 0 -b;
    // }
    fp_abs(&a);
    fp_abs(&b);

    return a + b;
}

int main() {
    int a = SumABS(-3, -2, MyAbsolute);

    // int a = -3;

    // MyAbsolute(&a);

    printf("%d \n", a);

    int b = SumABS(-3, -2, NULL);
    printf("%d \n", b);

    return 0;
}