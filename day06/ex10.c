#include <stdio.h>
#include <SDL2/SDL.h>

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL : %s \n", SDL_GetError());
        return 1;
    }
    else {
        printf("success SDL INIT\n");
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
                case SDL_QUIT:
                    bLoop = SDL_FALSE;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    printf("%d [%4d%4d]\n", event.button.button, event.motion.x, event.motion.y);
                    break;
                case SDL_MOUSEMOTION :
                    printf("[%4d%4d] \r", event.motion.x, event.motion.y);
                    break;
            }
        }
    }

    SDL_DestroyWindow(gWindow);

    return 1;
}