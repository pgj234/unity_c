#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Uint16 map_layer1[64] = {
    57, 65, 65, 74, 74, 65, 65, 56,
    65, 65, 65, 74, 74, 65, 65, 65,
    2, 0, 65, 74, 74, 65, 13, 13,
    65, 65, 65, 89, 89, 65, 13, 13,
    4, 6, 65, 74, 74, 65, 21, 21,
    65, 65, 65, 74, 74, 65, 21, 21,
    0, 2, 65, 74, 74, 65, 21, 21,
    12, 12, 65, 74, 74, 65, 65, 65
};

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

SDL_Window *gWindow;
SDL_Renderer *gRenderer;
SDL_Texture *gTexture;

void _drawDot(int x, int y, Uint8 _r, Uint8 _g, Uint8 _b)
{
    SDL_Rect _dotInfo;
    _dotInfo.x = x * 16;
    _dotInfo.y = y * 16;
    _dotInfo.w = 16;
    _dotInfo.h = 16;

    SDL_SetRenderDrawColor(gRenderer, _r, _g, _b, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(gRenderer, &_dotInfo);
}

void _drawTile(int x, int y, Uint16 _tileIndex) {
    SDL_Rect _tmpSrcRt;
    _tmpSrcRt.x = (_tileIndex % 8) * 16;
    _tmpSrcRt.y = (_tileIndex / 8) * 16;
    _tmpSrcRt.w = 16;
    _tmpSrcRt.h = 16;

    SDL_Rect _tmpDstRt;
    _tmpDstRt.x = x*64;
    _tmpDstRt.y = y*64;
    _tmpDstRt.w = 64;
    _tmpDstRt.h = 64;

    SDL_RenderCopy(gRenderer, gTexture, &_tmpSrcRt, &_tmpDstRt);
}

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL : %s \n", SDL_GetError());
        return 1;
    }

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        printf("SDL_image could not initialize! SDL_image Error : %s\n", IMG_GetError());
        return 0;
    }

    gWindow = SDL_CreateWindow("Game",
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    if (!gWindow) {
        printf("error initialiazing SDL : %s\n", SDL_GetError());
        return 1;
    }

    Uint32 render_flags = SDL_RENDERER_ACCELERATED;

    gRenderer = SDL_CreateRenderer(gWindow, -1, render_flags);

    if (!gRenderer) {
        printf("error initializing SDL : %s \n", SDL_GetError());
        return 1;
    }

    //이미지 로딩
    {
        SDL_Surface *surface;

        surface = IMG_Load("../res/basictiles.png");
        if (!surface) {
            printf("SDL_image could not initialize! SDL_image Error : %s\n", IMG_GetError());
            return 1;
        }

        SDL_Texture *tex = SDL_CreateTextureFromSurface(gRenderer, surface);

        gTexture = tex;

        SDL_FreeSurface(surface);
    }

    //게임루프
    SDL_bool bLoop = SDL_TRUE;
    while (bLoop) {
        //입력처리
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    bLoop = SDL_FALSE;
                    break;
                default:
                    break;
            }
        }

        // 출력(렌더링)
        SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(gRenderer);

        for (int iy = 0; iy < 8; iy++) {
            for (int ix = 0; ix < 8; ix++) {
                //Uint16 _dot = map_layer1[iy][ix];
                Uint16 _dot = map_layer1[iy * 8 + ix];
                int _x, _y;
                _x = ix + 0;
                _y = iy + 0;
                _drawTile(_x, _y, _dot);
            }
        }

        SDL_RenderPresent(gRenderer);
    }

    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
    return 0;
}