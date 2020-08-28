#include <stdio.h>

int main() {
    int a = 0x12345678;

    int *p = &a;

    char num1 = *((char *)p +3);
    char num2 = *((char *)p +2);
    short num3 = *((short *)p);

    printf("%x %x %x \n", num1, num2, num3);

    return 0;
}