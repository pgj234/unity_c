#include <stdio.h>
#include <SDL2/SDL.h>

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL : %s \n", SDL_GetError());
        return 1;
    }

    Uint32 a = 0x12345678;
    Uint8 *pA;
    pA = &a;

    for (int i=0; i<4; i++) {
        printf("%3x", *(pA+i));
    }
    printf("\n");

    SDL_Quit();
    return 0;
}