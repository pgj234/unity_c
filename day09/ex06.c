#include <stdio.h>

int t;

int main() {
    char a = 0x12, b = 0x34;
    short c = 0x5678;

    int arr[4] = {a, b, c, t};

    *( (char *)arr +15) = a;
    *( (char *)arr +14) = b;
    *( (short *)arr +6) = c;
    //printf("%8x %8x %8x %8x", arr[0], arr[1], arr[2], arr[3]);

    t = arr[3];

    printf("%8x", t);

    return 0;
}