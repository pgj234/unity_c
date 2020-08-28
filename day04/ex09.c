#include <stdio.h>

int main() {
    int data = 7;

    printf("[%d] [%5d] \n", data, data);
    printf("[%5d] \n", data * 11);
    printf("[%5d] \n", data);
    printf("[%-5d] \n", data);
    printf("[%05d] \n", data);

    float pi = 3.141592;

    printf("[%f] [%10f] [%6.2f] [%-6.2f] \n", pi, pi, pi, pi);

    printf("\n \\ [ T ] / \n");

    return 0;
}