#include <stdio.h>

void test() {
    #ifdef  __DEBUG__

    printf("debug mode \n");

    #endif
    printf("hello define \n");
}

#define MSG "hello"

#define MYINT int
typedef int _MYINT;

int main() {
    test();
    puts(MSG);

    int a=1;
    MYINT b=1;
}