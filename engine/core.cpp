#include "core.h"
#include <time.h>

tDE_S_Core *tDE_setup_1(const char *szTitle, int window_width, int window_height, Uint32 flags) {
    if (SDL_Init(SDL_INIT_EVERYTHING)) {
        printf("sdl init error : %s \n", SDL_GetError());
        return NULL;
    }
    
    tDE_S_Core *pCore = (tDE_S_Core*)SDL_malloc(sizeof(tDE_S_Core));

    pCore->m_pWin = SDL_CreateWindow(szTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, flags);
    pCore->m_ScreenWidth = window_width;
    pCore->m_ScreenHeight = window_height;

    pCore->m_pRender = SDL_CreateRenderer(pCore->m_pWin, -1, SDL_RENDERER_ACCELERATED);
    if (!IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) {
        printf("sdl_image dll init error : %s \n", SDL_GetError());
        return NULL;
    }

    if (TTF_Init() == -1) {
        printf("sdl_ttf dll init error : %s \n", SDL_GetError());
        return NULL;
    }

    pCore->m_pDefaultFont = TTF_OpenFont("../res/font/NanumMyeongjo.ttf", 20);
    if (!pCore->m_pDefaultFont) {
        printf("load default font error : %s \n", SDL_GetError());
    }

    printf("init module OK!");
    printf("engine start at %8d \n", time(NULL));
    srand(time(NULL));

    return pCore;
}

void tDE_closeCore(tDE_S_Core *pCore) {
    TTF_CloseFont(pCore->m_pDefaultFont);
    SDL_DestroyRenderer(pCore->m_pRender);
    SDL_DestroyWindow(pCore->m_pWin);
}

SDL_Texture *tDE_util_loadTexture(tDE_S_Core *pCore, const char *filename) {
    SDL_Surface *surface;
    surface = IMG_Load(filename);

    if (surface == NULL) {
        printf("file load error : %s", SDL_GetError());
        return NULL;
    }
    else {
        printf("load success %s \n", filename);
    }

    SDL_Texture *pTex = SDL_CreateTextureFromSurface(pCore->m_pRender, surface);
    SDL_FreeSurface(surface);

    return pTex;
}

SDL_bool tDE_util_parseSheet(char *str, tDE_S_SheetData *pData) {
    char *token = strtok(str, " ");
    if (!strcmp(token, "\t<SubTexture")) {
        static char _buf[5][256];

        // name
        token = strtok(NULL, " ");
        strcpy(_buf[0], token);

        // x
        token = strtok(NULL, " ");
        strcpy(_buf[1], token);

        // y
        token = strtok(NULL, " ");
        strcpy(_buf[2], token);

        // w
        token = strtok(NULL, " ");
        strcpy(_buf[3], token);

        // h
        token = strtok(NULL, " ");
        strcpy(_buf[4], token);

        // name 파싱
        token = strtok(_buf[0], "=");
        token = strtok(NULL, ".");
        strcpy(_buf[0], token +1);
        strcpy(pData->name, _buf[0]);

        // x 파싱
        token = strtok(_buf[1], "\"");
        token = strtok(NULL, "\"");
        pData->m_area.x = atoi(token);

        // y 파싱
        token = strtok(_buf[2], "\"");
        token = strtok(NULL, "\"");
        pData->m_area.y = atoi(token);

        // w 파싱
        token = strtok(_buf[3], "\"");
        token = strtok(NULL, "\"");
        pData->m_area.w = atoi(token);

        // h 파싱
        token = strtok(_buf[4], "\"");
        token = strtok(NULL, "\"");
        pData->m_area.h = atoi(token);

        return SDL_TRUE;
    }

    return SDL_FALSE;
}

SDL_Texture* tDE_util_createTextTexture(SDL_Renderer* pRenderer, TTF_Font* pFont, const char* text, SDL_Rect* ptextRect) {
    // const Uint16 *text = L"게임 시작";
    SDL_Color _whiteColor = { 0xff, 0xff, 0xff, 0xff };
    SDL_Surface* textSurface = TTF_RenderUTF8_Solid(pFont, text, _whiteColor);
    SDL_Texture* ptex = SDL_CreateTextureFromSurface(pRenderer, textSurface);

    ptextRect->w = textSurface->w;
    ptextRect->h = textSurface->h;

    SDL_FreeSurface(textSurface);

    // g_pTextTxture = ptex;
    return ptex;
}