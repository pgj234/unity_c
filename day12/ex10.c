#include <stdio.h>

int main() {
    unsigned char data;

    FILE *fp = fopen("test5.bin", "rb");
    fseek(fp, 2, SEEK_SET);
    fread(&data, sizeof(unsigned char), 1, fp);
    printf("%d \n", data);

    fseek(fp, 0, SEEK_SET);
    fread(&data, sizeof(unsigned char), 1, fp);
    printf("%d \n", data);

    fread(&data, sizeof(unsigned char), 1, fp);
    printf("%d \n", data);

    fclose(fp);

    printf("done! \n");

    return 0;
}