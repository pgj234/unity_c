#include <stdio.h>

int main() {
    char szBuf[32];
    FILE *fp = fopen("test.txt", "rt");

    fscanf(fp, "%s", szBuf);
    printf("read string : %s \n", szBuf);

    int data;
    fscanf(fp, "%x", &data);
    printf("read data : %x \n", data);

    fclose(fp);
}