#include <stdio.h>
#include <SDL2/SDL.h>

extern int result;
void Sum(int data1, int data2);

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL : %s \n", SDL_GetError());
        return 1;
    }

    printf("%d \n", result);

    SDL_Quit();
    return 0;
}