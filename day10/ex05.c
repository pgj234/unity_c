#include <stdio.h>

int main() {
    char data[3][2] = {
        {1, 2},
        {3, 4},
        {5, 6}
    };

    char (*pData)[2] = data;

    printf("%d, %d \n", data[1][0], pData[1][0]);
    printf("%d \n", *(pData +1)[1]);

    return 1;
}