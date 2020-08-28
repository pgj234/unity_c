#include <stdio.h>

int main() {
    int data = 5;

    puts("input : ");
    scanf("%d", &data);

    if (data == 10) {
        data = 0;
    }
    else {
        data++;
    }

    printf("%d \n", data);

    return 1;
}