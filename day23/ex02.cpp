#include <iostream>
#include <stdio.h>

int main() {

    static unsigned char buf[10000];
    FILE *fp = fopen("../sheet.bin", "rb");

    fread(buf, sizeof(buf)/sizeof(char), 1, fp);

    fclose(fp);

    return 0;
}