#include <stdio.h>

int main() {
    int input_data;

    input_data = getchar();
    rewind(stdin);
    printf("%d \n", input_data);
    
    //getchar();
    //printf("%d", input_data);
    input_data = getchar();
    printf("%d \n", input_data);

    return 0;
}