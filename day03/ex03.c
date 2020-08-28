#include <stdio.h>

int main() {
    printf("input number : ");
    int num;
    
    scanf("%d", &num);
    printf("10 : %d, 16 : %x, 8 : %o \n", num, num, num);

    return 0;
}