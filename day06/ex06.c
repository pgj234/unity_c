#include <SDL2/SDL.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL : %s \n", SDL_GetError());
        return 1;
    }
    else {
        printf("success SDL INIT\n");
    }

    int m = 0;
    SDL_bool bLoop = SDL_TRUE;

    while (bLoop) {
        m++;

        if (m >= 5) {
            //bLoop = SDL_FALSE;
            break;
        }
    if (m == 2) continue;

        printf("m=%2d \n", m);
        SDL_Delay(200);
    }

    return 0;
}