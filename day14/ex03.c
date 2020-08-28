#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

#include "../engine/ui_base.h"
#include "../engine/text_lable.h"
#include "../engine/button.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
SDL_Window *g_pWindow;
SDL_Renderer *g_pRenderer;
TTF_Font *g_pFont;

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

    if (!g_pFont) {
        printf("font file load error");
        printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
        return 0;
    }
    else {
        printf("font load ok!\n");
    }

    void *pUiObjs[3];

    pUiObjs[0] = createLable(g_pRenderer, 100, 100, 1, L"hello Lable 한글.0", g_pFont);
    pUiObjs[1] = createLable(g_pRenderer, 100, 130, 2, L"hello Lable 한글.1", g_pFont);
    //ptxLable[2] = createLable(g_pRenderer, 100, 160, 2, L"hello Lable 한글.2", g_pFont);
    pUiObjs[2] = createButton(g_pRenderer, WINDOW_WIDTH / 2 - 60, WINDOW_HEIGHT / 2 - 16, 120, 32, 1, L"나가기", g_pFont, NULL);

    SDL_bool bLoop = SDL_TRUE;

    while (bLoop) {
        SDL_SetRenderDrawColor(g_pRenderer, 0, 0, 0, 0xff);
        SDL_RenderClear(g_pRenderer);

        for (int i = 0; i < 3; i++) {
            ((S_UIBase *)pUiObjs[i])->m_fpRender(pUiObjs[i], g_pRenderer);
            // int nType = ((S_TextLable *)pUiObjs[i])->m_nType;

            // if( nType == 1) {
            //     ((S_TextLable *)pUiObjs[i])->m_fpRender(pUiObjs[i],g_pRenderer);
            // }
            // else if(nType == 2) {
            //     ((S_BUTTON *)pUiObjs[i])->m_fpRender(pUiObjs[i],g_pRenderer);
            // }

        //TextLable_render(ptxLable[i], g_pRenderer);
        }

        SDL_RenderPresent(g_pRenderer);

        SDL_Event _event;

        while (SDL_PollEvent(&_event)) {
            // Button_DoEvent(pButton,&_event);
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

    for (int i = 0; i < 3; i++) {
        ((S_UIBase *)pUiObjs[i])->m_fpDestroy(pUiObjs[i]);
        // int nType = ((S_TextLable *)pUiObjs[i])->m_nType;

        // if(nType==1) {
        //     ((S_TextLable *)pUiObjs[i])->m_fpDestory(pUiObjs[i]);
        // }
        // else if(nType==2) {
        //     ((S_BUTTON *)pUiObjs[i])->m_fpDestory(pUiObjs[i]);
        // }
        //TextLable_destory(ptxLable[i]);
    }

    TTF_CloseFont(g_pFont);
    SDL_DestroyRenderer(g_pRenderer);
    SDL_DestroyWindow(g_pWindow);
    SDL_Quit();

    return 0;
}