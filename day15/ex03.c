#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "../engine/ui_base.h"
#include "../engine/text_Lable.h"
#include "../engine/button.h"
#include "../engine/input_text.h"

const Uint16 WINDOW_WIDTH = 640;
const Uint16 WINDOW_HEIGHT = 480;

SDL_Window *g_pWindow;
SDL_Renderer *g_pRenderer;
TTF_Font *g_pFont;
S_TextLable *g_pLabelMainmenu;
S_BUTTON *g_pBtnExit;
S_INPUT_TEXT *g_pInputText;

void onPushExitButton(S_BUTTON *pBtn) {
    //종료 버튼 처리
    SDL_Event _evt;
    _evt.type = SDL_QUIT;
    SDL_PushEvent(&_evt);
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

    g_pRenderer = SDL_CreateRenderer(g_pWindow , -1, SDL_RENDERER_ACCELERATED);
    TTF_Init();
    g_pFont = TTF_OpenFont("../res/font/NanumMyeongjo.ttf", 28);
    g_pLabelMainmenu = myui_createLable(g_pRenderer, 0, 0, 1, L"메인메뉴", g_pFont);

    g_pBtnExit = myui_createButton(g_pRenderer, 0, 150, 96, 48, 2, L"종료", g_pFont, onPushExitButton);

    SDL_Color _fg = {0xff, 0xff, 0xff, 0xff};
    SDL_Color _bg = {0x80, 0x80, 0x80, 0xff};

    g_pInputText = myui_createInputText(g_pRenderer, 0, 65, 196, 32, 3, g_pFont, _fg, _bg);

    SDL_bool bLoop = SDL_TRUE;

    while (bLoop) {
        SDL_SetRenderDrawColor(g_pRenderer, 0x00, 0x00, 0xff, 0xff);
        SDL_RenderClear(g_pRenderer);
        g_pLabelMainmenu->m_base.m_fpRender(g_pLabelMainmenu,g_pRenderer);
        g_pBtnExit->m_base.m_fpRender(g_pBtnExit, g_pRenderer);
        g_pInputText->m_base.m_fpRender(g_pInputText, g_pRenderer);

        SDL_RenderPresent(g_pRenderer);

        SDL_Event _event;

        while (SDL_PollEvent(&_event)) {
            g_pBtnExit->m_base.m_fpDoEvent(g_pBtnExit, &_event);
            g_pInputText->m_base.m_fpDoEvent(g_pInputText, &_event);

            switch (_event.type) {
                case SDL_KEYDOWN:
                    // printf("%d \n", _event.key.keysym.scancode);
                    break;
                case SDL_QUIT:
                    bLoop = SDL_FALSE;
                    break;
                default:
                    break;
            }
        }
    }

    g_pBtnExit->m_base.m_fpDestroy(g_pBtnExit);
    g_pLabelMainmenu->m_base.m_fpDestroy(g_pLabelMainmenu);
    TTF_CloseFont(g_pFont);
    SDL_DestroyRenderer(g_pRenderer);

    SDL_DestroyWindow(g_pWindow);
    SDL_Quit();

    return 0;
}