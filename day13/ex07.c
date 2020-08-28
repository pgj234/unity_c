#include <stdio.h>
#include <SDL2/SDL.h>
#include "../engine/util.h"
#include "../engine/button.h"

const Uint16 WINDOW_WIDTH = 640;
const Uint16 WINDOW_HEIGHT = 480;
SDL_Window *g_pWindow;
SDL_Renderer *g_pRenderer;

SDL_bool bLoop = SDL_TRUE;

S_BUTTON g_Button[5];
const int size_gBtn = sizeof(g_Button) / sizeof(S_BUTTON);
//void (*btn_Arr[size_gBtn])(S_BUTTON *pBtn, int x, int y, int w, int h, Uint16 btnID);

int main(int argc, char *argv[]) {
    Button_Init(&g_Button[0], 125, 100, 120, 120, 1);
    Button_Init(&g_Button[1], 350, 100, 120, 120, 2);
    Button_Init(&g_Button[2], 50, 300, 120, 120, 3);
    Button_Init(&g_Button[3], 250, 300, 120, 120, 4);
    Button_Init(&g_Button[4], 450, 300, 120, 120, 5);
/*
    for (int i=0; i<size_gBtn; i++) {
        btn_Arr[i] = Button_Init;
        btn_Arr[i](&g_Button[i], 125, 100, 120, 120, i);
    }
*/
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }

    g_pWindow = SDL_CreateWindow("GAME", // creates a window
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, SDL_RENDERER_ACCELERATED);

    if (!g_pWindow) {
        printf("error initializing SDL window: %s\n", SDL_GetError());
        return 1;
    }

    while (bLoop) {
        SDL_SetRenderDrawColor(g_pRenderer, 0, 0, 0, 255);
        SDL_RenderClear(g_pRenderer);

        for (int i=0; i<size_gBtn; i++) {
            Button_Render(&g_Button[i], g_pRenderer);
        }

        SDL_RenderPresent(g_pRenderer);

        SDL_Event _event;
        while (SDL_PollEvent(&_event)) {
            for (int i=0; i<size_gBtn; i++) {
                Button_DoEvent(&g_Button[i], &_event);
            }

            switch (_event.type) {
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