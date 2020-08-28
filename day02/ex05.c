#include <stdio.h>

int main() {
    char _operation;
    int _a, _b;

    printf("input : ");
    scanf("%d %c %d", &_a, &_operation, &_b);

    if (_operation == '+') {        //덧셈
        printf("%d %c %d = %d \n", _a, _operation, _b, _a + _b);
    }
    else if (_operation == '-') {   //뺄셈
        printf("%d %c %d = %d \n", _a, _operation, _b, _a - _b);
    }
    else if (_operation == '*') {    //곱셈
        printf("%d %c %d = %d \n", _a, _operation, _b, _a * _b);
    }
    else if (_operation == '/') {    //나눗셈
        printf("%d %c %d = %d \n", _a, _operation, _b, _a / _b);
    }
    else if (_operation == '%') {   //나머지
        printf("%d %c %d = %d \n", _a, _operation, _b, _a % _b);

    }
    else {
        printf("operation error \n");
    }

    return 0;
}