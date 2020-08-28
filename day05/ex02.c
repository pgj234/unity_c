#include <stdio.h>

int main() {
    int i = 5;
    int a;

    printf("%d \n", i);

    i++;
    printf("%d \n", i);

    a = i++;
    printf("%d \n", a);
    printf("%d \n", i);

    a = ++i;
    printf("%d \n", a);

    return 1;
}