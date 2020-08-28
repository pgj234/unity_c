#include <stdio.h>

void main() {
    short birthday;
    birthday = 24;

    //short *, int *, char *
    short *ptr = &birthday;

    printf("%d %d\n", birthday, &birthday);
    printf("%d, %d \n", *ptr, ptr);
}