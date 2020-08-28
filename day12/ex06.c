#include <stdio.h>

int main() {
    int kor, eng, math;

    FILE *fp = fopen("test2.txt", "rt");

    while (EOF != fscanf(fp, "%d %d %d", &kor, &eng, &math)) {
        printf("%d %d %d \n", kor, eng, math);
    }

    return 0;
}