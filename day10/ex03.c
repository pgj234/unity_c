#include <stdio.h>

int main() {
    int data[5] = {1, 2, 3, 4, 5};
    int *pData = data;

    for (int i=0; i<5; i++) {
        //printf("%d \n", data[i]);
        //printf("%d \n", *pData++);
        //pData++;
        printf("%d \n", *(pData++));
    }

    return 0;
}