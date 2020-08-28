#include <stdio.h>

int main() {
    unsigned char data[8] = {10, 20, 30, 0, 50, 60, 70, 80};

    FILE *fp = fopen("test5.bin", "wb");

    fwrite(data, sizeof(unsigned char), 8, fp);

    fclose(fp);

    printf("done! \n");

    return 0;
}