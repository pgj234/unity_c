#include <stdio.h>

int main() {
    putchar('A');
    printf("\n");
    
    putchar(67);
    printf("\n");
    
    putc('B', stdout);
    printf("\n");

    puts("hello hello");

    return 1;
}