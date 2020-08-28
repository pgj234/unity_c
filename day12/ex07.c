#include <stdio.h>

int main() {
    char strBuf[32];

    FILE *fp = fopen("test3.txt", "rt");

    while(NULL != fgets(strBuf, sizeof(strBuf), fp)) {
        puts(strBuf);
    }

    // while (EOF != fscanf(fp, "%s", strBuf)) {
    //     puts(strBuf);
    // }

    fclose(fp);

    return 0;
}