#include <SDL2/SDL.h>
#include <stdio.h>

int main(int argc, char* argv[]) {

    if (SDL_Init(SDL_INIT_EVERYTHING != 0)) {
        printf("error initializing SDL : %s \n", SDL_GetError());
        return 1;
    }

    SDL_Window *gWindow = SDL_CreateWindow("Gam",
                                            SDL_WINDOWPOS_CENTERED,
                                            SDL_WINDOWPOS_CENTERED,
                                            640, 480, 0);
    SDL_bool bLoop = SDL_TRUE;

    while (bLoop) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN:
                printf("%d \n", event.key.keysym.scancode);

                if (event.key.keysym.scancode == 41) {
                    bLoop = SDL_FALSE;
                }
                break;

                default :
                break;
            }
        }
    }

    return 0;
}