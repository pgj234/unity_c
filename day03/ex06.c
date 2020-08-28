#include <stdio.h>

int main() {
    float a = 1.52e-5;
    int _b = 0xFA;
    int _c = 012;
    int _d = 0b1011000;
    char *strMsg = "hello world";

    printf("%f \n %d \n %d \n %d \n %s \n", a, _b, _c, _d, strMsg);

    return 0;
}