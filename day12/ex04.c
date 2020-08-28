#include <stdio.h>

int main() {

    char szBuf[32];
    gets(szBuf);

    FILE *fp = fopen("test.txt", "wt");

    if (!fp) {
        printf("file error \n");
    }
    else {
        printf("open success \n");
        int _count = fprintf(fp, "%s \n", szBuf);
        printf("%d byte write \n", _count);

        short data = 0x0412;
        _count = fprintf(fp, "%x \n", data);
        printf("%d byte write \n", _count);
    }

    fclose(fp);

    puts(szBuf);

    return 0;
}