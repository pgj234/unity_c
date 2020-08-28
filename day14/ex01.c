#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "../engine/button.h"

const Uint16 WINDOW_WIDTH = 640;
const Uint16 WINDOW_HEIGHT = 480;

SDL_Window *g_pWindow;
SDL_Renderer *g_pRenderer;
TTF_Font *g_pFont;

S_BUTTON *g_pExitButton;

static SDL_bool bLoop = SDL_TRUE;

void callbackExitButtonPush(S_BUTTON *pBtn) {
    bLoop = SDL_FALSE;
}

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

    g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, SDL_RENDERER_ACCELERATED);

    //Initialize SDL_ttf
    if (TTF_Init() == -1) {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        return 0;
    }
    else {
        printf("SDL_ttf initialize Ok!  \n");
    }

    //LOAD font file
    g_pFont = TTF_OpenFont("../res/font/NanumMyeongjo.ttf", 28);

    Uint16 _text[] = {L'나', L'가',L'기',0x0000};

    g_pExitButton = createButton(g_pRenderer, WINDOW_WIDTH / 2 - 60, WINDOW_HEIGHT / 2 - 16, 120, 32, 1, _text, g_pFont, callbackExitButtonPush);

    //game loop
    while (bLoop) {
        //rendering
        SDL_SetRenderDrawColor(g_pRenderer, 0, 0, 0, 0xff);
        SDL_RenderClear(g_pRenderer);

        Button_Render(g_pExitButton, g_pRenderer);

        SDL_RenderPresent(g_pRenderer);

        //event handling
        SDL_Event _event;

        while (SDL_PollEvent(&_event)) {
            Button_DoEvent(g_pExitButton, &_event);

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
  
    destoryButton(g_pExitButton);
    TTF_CloseFont(g_pFont);

    SDL_DestroyRenderer(g_pRenderer);
    SDL_DestroyWindow(g_pWindow);
    SDL_Quit();

    return 0;
}