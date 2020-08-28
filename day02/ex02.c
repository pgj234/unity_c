#include <stdio.h>

int main() {
    int test_var1, test_var2;

    test_var1 = 20;
    printf("value is %d \n", test_var1);

    test_var1 = 30;
    printf("value is %d \n", test_var1);

    printf("value is %d \n", test_var1 + 10);

    test_var2 = 15;

    printf("value is %d \n", test_var1 + test_var2);

    return 0;
}