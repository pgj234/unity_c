#include <stdio.h>
#include <malloc.h>

typedef unsigned int UInt;
typedef unsigned char UChar;
typedef UChar *PTRchar;

typedef int myData[5];

int main() {
    //d[5] = {1, 2, 3, 4, 5};
    unsigned int a = 1;
    UInt b = 2;
    UChar c = 128;
    //char *ptr;
    PTRchar ptr;
    ptr = &c;
    myData _p = {1, 2, 3, 4, 5};

    printf("%d %d %d %d %d\n", a, b, c, *ptr, _p[0]);

    myData *p;
    p = (myData *)malloc(sizeof(myData));
    (*p)[0] = 3;
    printf("%d \n", (*p)[0]);
}