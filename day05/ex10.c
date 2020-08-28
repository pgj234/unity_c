#include <stdio.h>

int main() {
    int point;
    int value = 50000;

    point = (value >= 10000) ? value * 0.1 : value * 0.01;

/*
    if(value >= 10000) {
        value *= 0.1;
    }
    else {
        value *= 0.01;
    }

    printf("%d \n", value);
*/
    
    printf("%d \n", point);

    return 1;
}