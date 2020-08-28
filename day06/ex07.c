#include <stdio.h>
#include <SDL2/SDL.h>

int main(int argc, char *argv[]) {
    char num = 1;   //0000 0001

    printf("%d \n", num << 1, num << 1);    //0000 0010
    printf("%d \n", num << 2, num << 2);    //0000 0100

    num = 8; //0000 1000

    printf("%d \n", num << 1, num << 1);    //0001 0000
    printf("%d \n", num << 2, num << 2);    //0010 0000

    return 0;
}