#include <stdio.h>
#include "ex04.h"

int main() {
    int rest = Sum(7, 15);
    int rest2 = Mul(3, 6);
    int rest3 = Sub(12, 3);
    int rest4 = Div(20, 8);
    printf("sum result : %d \n", rest);
    printf("mul result : %d \n", rest2);
    printf("Sub result : %d \n", rest3);
    printf("Div result : %d \n", rest4);
    return 1;
}