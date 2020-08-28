#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdio.h>
#include <malloc.h>
#include <memory.h>

typedef struct _struct {
    char name[32];
    unsigned short x;
    unsigned short y;
    unsigned short w;
    unsigned short h;
} _Struct;

int get_data_size(FILE *fp) {
    fseek(fp, 0, SEEK_END);
    int _size = ftell(fp);
    int _count = _size / sizeof(_Struct);
    fseek(fp, 0, SEEK_SET);

    return _count;
}

void trim_space(char* str) {
    for (int i = 31; i > 0; i--) {
        if (str[i] != 0x20) {
            str[i + 1] = 0x00;
            break;
        }
    }
}

int main() {
    FILE* fp = fopen("../sheet2.bin", "rb");
    int _data_size = get_data_size(fp);
    printf("data size : %d \n", _data_size);

    void* ptrBuf;
    ptrBuf = malloc(_data_size * sizeof(_Struct));
    fread(ptrBuf, sizeof(_Struct), _data_size, fp);
    fclose(fp);

    for (int i = 0; i < _data_size; i++) {
        _Struct* pSheet = ((_Struct*)ptrBuf + i);
        //pSheet->name[31] = 0x00;
        trim_space(pSheet->name);
        printf("X : %4d, Y : %4d, W : %4d, H : %4d,   Name : %32s\n", pSheet->x, pSheet->y, pSheet->w, pSheet->h, pSheet->name);
    }

    free(ptrBuf);
    return 0;
}