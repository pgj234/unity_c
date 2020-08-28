#include <stdio.h>

int Sum(int val1, int val2) {
    int result = val1 + val2;
    return result;
}

void Test() {
    printf("test call 1 \n");
    return;
    printf("test call 2 \n");
}

void main() {
    int val1, val2;

    printf("input : ");
    scanf("%d %d", &val1, &val2);

    printf("Sum Result : %d \n", Sum(val1, val2));
    Test();
    printf("/ [ T ] / \n");
}