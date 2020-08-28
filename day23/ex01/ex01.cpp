#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdio.h>

typedef struct _struct {
    unsigned short x;
    unsigned short y;
    unsigned short w;
    unsigned short h;
} _Struct;

int main() {

    static unsigned char buf[10000];
    FILE* fp = fopen("../sheet.bin", "rb");

    fseek(fp, 0, SEEK_END);
    int _size = ftell(fp);

    int _count = _size / sizeof(_Struct);

    fseek(fp, 0, SEEK_SET);
    fread(buf, sizeof(buf) / sizeof(char), 1, fp);
    printf("read bytes : %d\n", _count);
    
    _Struct* ptr = (_Struct*)buf;
    for (int i = 0; i < _count; i++) {
        printf("\nx : %4d\ny : %4d\nw : %4d\nh : %4d\n", ptr->x, ptr->y, ptr->w, ptr->h);
        ptr++;
    }

    //printf("\nx : %4d\ny : %4d\nw : %4d\nh : %4d\n", ptr->x, ptr->y, ptr->w, ptr->h);

    fclose(fp);

    return 0;
}