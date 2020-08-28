#include <stdio.h>

struct Test_1 {
    char a;
    double b;
    short c;
    char d;
};

struct Test_2 {
    char a;
    char d;
    short c;
    double b;
};

int main() {
    printf("test 1 : %d, test 2 : %d \n", sizeof(struct Test_1), sizeof(struct Test_2));

    return 0;
}