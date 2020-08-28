#include <stdio.h>

int main() {
    int data[3] = {0x12345678, 0x12345678, 0x12345678};

    //data[0] = 0x00;
    *(char *)(data+0) = 0x00;
    printf("%8x\n", data[0]);

    //data[1]
    *( (char *)data +6) = 0x00;
    printf("%8x\n", data[1]);

    //data[2]

    *( (char *)data +9) = 0x99;
    printf("%8x\n", data[2]);

    return 0;
}