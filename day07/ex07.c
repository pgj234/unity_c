#include <stdio.h>
#include <SDL2/SDL.h>

const float _PI = 3.14; //const 읽기전용 됨

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL : %s \n", SDL_GetError());
        return 1;
    }

    printf("%f \n", _PI);
    //_PI = 3.4;
    //printf("%f \n", _PI);

    SDL_Quit();
    return 0;
}