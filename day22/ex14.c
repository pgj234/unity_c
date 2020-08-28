#include <stdio.h>

int main() {
    short a = 0;
    short b = 0;
    int c = 0;
    char buf[8];

    FILE *fp = fopen("t1.bin", "rb");
    fread(buf, sizeof(buf)/sizeof(char), 1, fp);
    
    char *p = buf;

    a = *((short *)p);
    b = *((short *)p +1);
    c = *((int *)p +1);

    printf("\na : %x\nb : %x\nc : %x\n", a, b, c);

    return 0;
}