#include <stdio.h>
#include <SDL2/SDL.h>

int result; //  전역 변수

void _Sum(int data1, int data2) {
    // int result;
    result = data1 + data2;
}

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL : %s \n", SDL_GetError());
        return 1;
    }

    _Sum(5, 3);
    printf("%d \n", result);

    SDL_Quit();
    return 0;
}