#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

const Uint16 WINDOW_WIDTH = 640;
const Uint16 WINDOW_HEIGHT = 480;

SDL_Window *g_pWindow;
SDL_Renderer *g_pRenderer;
SDL_Texture *g_pTexture;

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

    g_pRenderer = SDL_CreateRenderer(g_pWindow , -1, SDL_RENDERER_ACCELERATED);
    
    {
        SDL_Surface *pSurf = IMG_Load("../res/characters.png");
        g_pTexture = SDL_CreateTextureFromSurface(g_pRenderer, pSurf);
        SDL_FreeSurface(pSurf);
    }

    SDL_Point position = {0, 0};

    SDL_bool bLoop = SDL_TRUE;

    while (bLoop) {
        SDL_SetRenderDrawColor(g_pRenderer, 0x00, 0x00, 0x00, 0xff);
        SDL_RenderClear(g_pRenderer);

        SDL_Rect srcRt = {16, 0, 16, 16};
        SDL_Rect dstRt = {position.x *32, position.y *32, 16 *2, 16 *2};
        SDL_RenderCopy(g_pRenderer, g_pTexture, &srcRt, &dstRt);

        SDL_RenderPresent(g_pRenderer);

        SDL_Event _event;

        while (SDL_PollEvent(&_event)) {

            switch (_event.type) {
                case SDL_KEYDOWN:
                    // printf("%d \n", _event.key.keysym.scancode);
                    // 82 Up, 81 Down, 80 Left, 79 Right
                    if (_event.key.keysym.scancode == 79) {
                        position.x += 1;
                    }
                    else if (_event.key.keysym.scancode == 80) {
                        position.x -= 1;
                    }
                    else if (_event.key.keysym.scancode == 81) {
                        position.y += 1;
                    }
                    else if (_event.key.keysym.scancode == 82) {
                        position.y -= 1;
                    }

                    printf("%4d%4d \r", position.x, position.y);
                    
                    break;
                case SDL_QUIT:
                    bLoop = SDL_FALSE;
                    break;
                default:
                    break;
            }
        }
    }

    SDL_DestroyRenderer(g_pRenderer);
    SDL_DestroyWindow(g_pWindow);
    SDL_Quit();

    return 0;
}