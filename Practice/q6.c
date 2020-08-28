#include <stdio.h>

int main() {
    char a[][4] = {
        {0x1,0x10,0x00,0x00},   // a1
        {0x2,0x20,0x00,0x00},   // a2
        {0x3,0x00,0x30,0x00},   // a3
        {0x4,0x00,0x40,0x00},   // a4
        {0x5,0x00,0x00,0x50}    // a5
    };

    int a1, a2, a3, a4, a5;
    int _a1, _a2, _a3, _a4, _a5;
    int sum;

    //리틀 엔디언
    char _temp[4];
    a1 = *(int *)a[0];
    printf("little : %08x\n", a1);

    //빅 엔디언
    _temp[0] = a[0][3];
    _temp[1] = a[0][2];
    _temp[2] = a[0][1];
    _temp[3] = a[0][0];
    _a1 = *(int *)_temp;
    printf("big? : %08x \n", _a1);

    a2 = *(int *)a[1];
    printf("%d \n", a2);

    // a1 = *((int *)a[0]);
    // a2 = *((int *)a[1]);
    // a3 = *((int *)a[2]);
    // a4 = *((int *)a[3]);
    // a5 = *((int *)a[4]);

    // printf("big : %x %x %x %x %x\n", a1, a2, a3, a4, a5);

    return 0;
}