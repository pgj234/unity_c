#include <stdio.h>

/*void Test() {
    printf("test call 1 \n");
}*/

void _test(char *);

void main() {
    //Test();
    _test("pgj pgj pgj");
}

void _test(char *strMsg) {
    printf("_test call 0 %s \n", strMsg);
}