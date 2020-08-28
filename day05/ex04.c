#include <stdio.h>

int main() {
    printf("%d %d %d %d \n",
        1 > 2,
        1 < 2,
        1 == 2,
        1 != 2
    );

    printf("%d \n", (1 == 1) && (2 > 1));   // AND
    printf("%d \n", (1 != 1) || (2 > 1));   // OR

    printf("%d \n", 1 && 1 && 1);   // 이중 AND
}