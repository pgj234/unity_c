#include <stdio.h>
#include <SDL2/SDL.h>
#include "../engine/util.h"

const Uint16 WINDOW_WIDTH = 640;
const Uint16 WINDOW_HEIGHT = 480;
SDL_Window *g_pWindow;
SDL_Renderer *g_pRenderer;

typedef struct {
    SDL_Rect m_Rect;
    //Uint16 m_nFSM;
    SDL_bool bCheckHitRect;
} S_BUTTON;

S_BUTTON g_Button[2];

int main(int argc, char *argv[]) {
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

    SDL_bool bLoop = SDL_TRUE;
    // SDL_bool bCheckHitRect = SDL_FALSE;
    // SDL_bool bCheckHitRect2 = SDL_FALSE;

    {
        S_BUTTON *pbtn = &g_Button[0];
        pbtn -> m_Rect.x = 100;
        pbtn -> m_Rect.y = 100;
        pbtn -> m_Rect.w = 120;
        pbtn -> m_Rect.h = 120;
        pbtn -> bCheckHitRect = SDL_FALSE;
    }
    {
        S_BUTTON *pbtn = &g_Button[1];
        pbtn -> m_Rect.x = 300;
        pbtn -> m_Rect.y = 100;
        pbtn -> m_Rect.w = 120;
        pbtn -> m_Rect.h = 120;
        pbtn -> bCheckHitRect = SDL_FALSE;
    }

    while (bLoop) {
        SDL_SetRenderDrawColor(g_pRenderer, 0, 0, 0, 255);
        SDL_RenderClear(g_pRenderer);
        
        //버튼 렌더
        for (int i=0; i<sizeof(g_Button) / sizeof(S_BUTTON); i++) {
            S_BUTTON *pBtn = &g_Button[i];
            if (pBtn -> bCheckHitRect) {
                SDL_SetRenderDrawColor(g_pRenderer, 255, 255, 255, 255);
                SDL_RenderDrawRect(g_pRenderer, &(pBtn->m_Rect));
            }
            else {
                SDL_SetRenderDrawColor(g_pRenderer, 100, 255, 100, 255);
                SDL_RenderFillRect(g_pRenderer, &(pBtn->m_Rect));
            }
        }

        // SDL_Rect testRect = {100, 100, 120, 120};
        // SDL_Rect testRect2 = {250, 250, 150, 150};

        // if (!bCheckHitRect) {    
        //     SDL_SetRenderDrawColor(g_pRenderer, 255, 255, 255, 255);
        //     SDL_RenderFillRect(g_pRenderer, &testRect);
        // }
        // else {
        //     SDL_SetRenderDrawColor(g_pRenderer, 255, 0, 0, 255);
        //     SDL_RenderFillRect(g_pRenderer, &testRect);
        // }

        // if (!bCheckHitRect2) {    
        //     SDL_SetRenderDrawColor(g_pRenderer, 255, 255, 255, 255);
        //     SDL_RenderFillRect(g_pRenderer, &testRect2);
        // }
        // else {
        //     SDL_SetRenderDrawColor(g_pRenderer, 255, 0, 0, 255);
        //     SDL_RenderFillRect(g_pRenderer, &testRect2);
        // }

        SDL_RenderPresent(g_pRenderer);

        SDL_Event _event;
        while (SDL_PollEvent(&_event)) {
            switch (_event.type) {
                case SDL_MOUSEBUTTONDOWN:
                    {
                        int mx = _event.motion.x;
                        int my = _event.motion.y;

                        for (int i=0; i<sizeof(g_Button) / sizeof(S_BUTTON); i++) {
                            if (checkPointInRect(&(g_Button[i].m_Rect), _event.motion.x, _event.motion.y) == SDL_TRUE) {
                                printf("button index %d down \n", i);
                            }
                        }

                        // if (checkPointInRect(&testRect, _event.motion.x, _event.motion.y) == SDL_TRUE) {
                        //     printf("push button 1 \n");
                        // }
                        // else if (checkPointInRect(&testRect2, _event.motion.x, _event.motion.y) == SDL_TRUE) {
                        //     printf("push button 2 \n");
                        // }
                    }
                    break;
                case SDL_MOUSEMOTION:
                    {
                        for (int i=0; i<sizeof(g_Button) / sizeof(S_BUTTON); i++) {
                            g_Button[i].bCheckHitRect = checkPointInRect(&(g_Button[i].m_Rect), _event.motion.x, _event.motion.y);
                        }

                        // bCheckHitRect = checkPointInRect(&testRect, _event.motion.x, _event.motion.y);
                        // bCheckHitRect2 = checkPointInRect(&testRect2, _event.motion.x, _event.motion.y);
                        // int mx = _event.motion.x;
                        // int my = _event.motion.y;

                        // if ((testRect.x < mx && testRect.y < my) && (testRect.x + testRect.w > mx) && (testRect.y + testRect.h > my)) {         //충돌 ON
                        //     printf("%4d%4d%2d\r", _event.motion.x, _event.motion.y, 1);
                        //     bCheckHitRect = SDL_TRUE;
                        // }
                        // else {                                                                                                              //충돌 OFF
                        //     printf("%4d%4d%2d\r", _event.motion.x, _event.motion.y, 0);
                        //     bCheckHitRect = SDL_FALSE;
                        // }
                    }
                    break;
                case SDL_KEYDOWN:
                    {
                        int _mx = _event.motion.x;
                        int _my = _event.motion.y;
                    }
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