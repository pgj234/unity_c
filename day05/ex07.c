#include <stdio.h>

int main() {

    int data = 8;

    if (data > 3) {
        printf(" bigger then 3 \n ");
        data = data % 3;
    }

    printf("finish %d \n", data);
}