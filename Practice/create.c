#include <stdio.h>

int main() {
    int data[100] = {0,};
    FILE *fp = fopen("q3.dat","wb");
    fwrite(data,sizeof(int),100,fp);
    fclose(fp);

    return 0;
}