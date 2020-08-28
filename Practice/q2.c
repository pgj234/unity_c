#include <stdio.h>

int main() {
    int a = 0x00030002;
    
    int *p = &a;

    short b = *((short *)p +1);
    short c = *((short *)p);

    printf("%x %x\n", b, c);

    short result = b + c;

    printf("%d", result);

    return 0;
}