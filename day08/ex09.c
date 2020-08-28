#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL : %s \n", SDL_GetError());
        return 1;
    }

    SDL_Window *gWindow;
    gWindow = SDL_CreateWindow("Game",
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                640, 480, 0);

    SDL_bool bLoop = SDL_TRUE;
    while (bLoop) {
        SDL_Event _event;
        while (SDL_PollEvent(&_event)) {
            if(_event.type == SDL_QUIT) bLoop = SDL_FALSE;
        }
        printf("%8d \r", rand()%100);
        SDL_Delay(500);
    }

    SDL_DestroyWindow(gWindow);
    SDL_Quit();
    return 0;
}