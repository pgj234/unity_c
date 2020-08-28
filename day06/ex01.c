#include <stdio.h>

void main() {
    //int sum = 0, num;
    //for (num=3; num<=5; num++)
    
    //int sum, num;
    //for (num = 1, sum = 0; num <= 5; num++)
    
    //int sum = 0;
    //for (int num=1; num <= 5; num++)
    
    int sum = 0, num = 1;
    for (; num <= 5;) {
        printf("%d \n", num);
        sum = sum + num;
        num++;
    }

    printf("result : %d \n", sum);
}