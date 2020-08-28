#include <stdio.h>

int main() {
    int i = 0;

    printf("%d \n", i++);
    printf("%d \n", i);

    printf("%d \n", ++i);

    printf("%d %d \n", ++i, ++i);

    printf("%d %d \n", i++, i++);

    return 1;
}