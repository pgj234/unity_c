#include <stdio.h>
#include <SDL2/SDL.h>

void Sum(int data1, int data2);
extern int result;

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL : %s \n", SDL_GetError());
        return 1;
    }

    Sum(5, 3);
    printf("%d \n", result);

    SDL_Quit();
    return 0;
}