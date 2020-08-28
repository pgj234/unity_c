#include <stdio.h>
#include <SDL2/SDL.h>

const Uint16 WINDOW_WIDTH = 640;
const Uint16 WINDOW_HEIGHT = 480;
SDL_Window *g_pWindow;

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }

    g_pWindow = SDL_CreateWindow("GAME", // creates a window
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    if (!g_pWindow) {
        printf("error initializing SDL window: %s\n", SDL_GetError());
        return 1;
    }

    SDL_bool bLoop = SDL_TRUE;
    
    while (bLoop) {
        SDL_Event _event;
    
        while (SDL_PollEvent(&_event)) {
            switch (_event.type) {
                case SDL_KEYDOWN:
                    printf("%d \n", _event.key.keysym.scancode);
                    break;
                case SDL_QUIT:
                    bLoop = SDL_FALSE;
                    break;
                default:
                    break;
            }
        }
    }

    SDL_DestroyWindow(g_pWindow);
    SDL_Quit();

    return 0;
}